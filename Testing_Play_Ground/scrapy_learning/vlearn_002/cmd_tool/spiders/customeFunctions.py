import pandas as pd
from bs4 import BeautifulSoup

def ul_to_dict(htmlul):
    ul=BeautifulSoup(htmlul).ul
    result = {}
    highlite=[]
    for li in ul.find_all("li", recursive=False):
        key = next(li.stripped_strings)
        data=key.split(":")
        if len(data)==2:
            result[data[0].strip()]=data[1].strip()
        else:
            highlite.append(data[0])
    return result,highlite