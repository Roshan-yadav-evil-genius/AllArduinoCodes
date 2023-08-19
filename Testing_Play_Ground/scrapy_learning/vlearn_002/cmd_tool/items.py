# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class CmdToolItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    title = scrapy.Field()
    image = scrapy.Field()
    price = scrapy.Field()
    discount = scrapy.Field()
    lowest = scrapy.Field()
    highest = scrapy.Field()
    ProductHistoryLink = scrapy.Field()
    PlatformLink = scrapy.Field()
    Platform = scrapy.Field()
    brand = scrapy.Field()
    ProductPage = scrapy.Field()
    PlatformPage = scrapy.Field()
    productOverview = scrapy.Field()
