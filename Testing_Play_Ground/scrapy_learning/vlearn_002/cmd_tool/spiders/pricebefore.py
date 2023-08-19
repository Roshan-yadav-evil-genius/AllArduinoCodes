
import scrapy
from ..items import CmdToolItem
import pandas as pd
from .customeFunctions import ul_to_dict

class AuthorSpider(scrapy.Spider):
    name = 'discount'

    start_urls = [
        'https://www.pricebefore.com/price-drops/?price-drop=todaysDeals',
        "https://www.pricebefore.com/price-drops/?price-drop=todaysDeals&page=2&more=true",
        "https://www.pricebefore.com/price-drops/?price-drop=todaysDeals&page=3&more=true",
        "https://www.pricebefore.com/price-drops/?price-drop=todaysDeals&page=4&more=true", ]

    def parse(self, response):
        products_wrapper = response.css("ul.product-list")

        for product in products_wrapper.css("li.item div.body"):
            items = CmdToolItem()
            items["title"] = product.css("div.title b a::text").get().strip()
            items["image"] = product.css("div.col-left a img::attr(data-src)").get()
            items["price"] = product.css("div.price span::text").get().replace("\u20b9", "Rs ")
            items["discount"] = product.css("div.price span.discount span.percent::text").get()
            items["lowest"] = product.css("div.price-overview div.item::text").get().replace("\u20b9", "Rs ")
            items["highest"] = product.css("div.price-overview div.item::text")[1].get().replace("\u20b9", "Rs ")
            items["Platform"] = product.css("div.btn-wrap").xpath("./a[@title='Go to Shop']/text()").get().strip("Buy on")
            if items["Platform"].lower()=="amaz":
                items["Platform"]="Amazon"
            PriceHistoryTitle = product.css("div.btn-wrap a::attr(title)").re(r".* Price History Chart")[0]
            items["ProductHistoryLink"] = product.css("div.btn-wrap").xpath(f"./a[@title='{PriceHistoryTitle}']/@href").get()


            items["PlatformLink"] = product.css("div.btn-wrap").xpath("./a[@title='Go to Shop']/@href").get()
            yield scrapy.Request(response.urljoin(items["ProductHistoryLink"]), callback=self.parse_HistoryScraper,cb_kwargs={'item':items})
           
     
    def parse_HistoryScraper(self,response,item):
        item["brand"] = response.css("table tr td.value a::text").get()
        yield scrapy.Request(response.urljoin(item["PlatformLink"]), callback=self.parse_FromPlatform, cb_kwargs={'item': item})
    
    def parse_FromPlatform(self,response,item):
        item["ProductPage"] = response.request.url
        
        if "amaz" in item["Platform"].lower():
            data = pd.read_html(response.css("div#productOverview_feature_div table").get())
            item["productOverview"] = {"overview": {key: value for key,value in data[0].to_dict("split")["data"]}}

        if item["Platform"].lower() == "flipkart":
            data = response.css("div._2418kt ul").get()
            data = ul_to_dict(data)
            item["productOverview"] = {"overview": data[0], "highlites": data[1]}

        yield item
