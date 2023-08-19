import scrapy


class AuthorSpider(scrapy.Spider):
    name = 'author'

    start_urls = [
        'https://www.amazon.in/s?k=phone']

    def parse(self, response):
        def parse_product_page(self, response):
        asin = response.meta['asin']
        title = response.xpath(
            '//*[@id="productTitle"]/text()').extract_first()
        image = re.search('"large":"(.*?)"', response.text).groups()[0]
        rating = response.xpath('//*[@id="acrPopover"]/@title').extract_first()
        number_of_reviews = response.xpath(
            '//*[@id="acrCustomerReviewText"]/text()').extract_first()
        bullet_points = response.xpath(
            '//*[@id="feature-bullets"]//li/span/text()').extract()
        seller_rank = response.xpath(
            '//*[text()="Amazon Best Sellers Rank:"]/parent::*//text()[not(parent::style)]').extract()
rs