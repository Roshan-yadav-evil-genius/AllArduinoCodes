import pandas as pd 
from bs4 import BeautifulSoup

data="""<table class="a-normal a-spacing-micro">  <tr class="a-spacing-small po-brand"> <td class="a-span3"> <span class="a-size-base a-text-bold">Brand</span> </td> <td class="a-span9">    <span class="a-size-base">Samsung</span>   </td> </tr>  <tr class="a-spacing-small po-style"> <td class="a-span3"> <span class="a-size-base a-text-bold">Style</span> </td> <td class="a-span9">    <span class="a-size-base">BT</span>   </td> </tr>  <tr class="a-spacing-small po-color"> <td class="a-span3"> <span class="a-size-base a-text-bold">Colour</span> </td> <td class="a-span9">    <span class="a-size-base">Pink Gold</span>   </td> </tr>  <tr class="a-spacing-small po-special_feature"> <td class="a-span3"> <span class="a-size-base a-text-bold">Special Feature</span> </td> <td class="a-span9">    <span class="a-size-base">Sleep Monitor, Activity Tracker, Heart Rate Monitor</span>   </td> </tr>  <tr class="a-spacing-small po-age_range_description"> <td class="a-span3"> <span 
class="a-size-base a-text-bold">Age Range (Description)</span> </td> <td class="a-span9">    <span class="a-size-base">Adult</span>   </td> </tr>  </table>
"""

data1="""
<ul><li class="_21Ahn-">Blade Material: Stainless Steel</li><li class="_21Ahn-">Trimming Range: 1 - 20 mm</li><li class="_21Ahn-">80 min battery run time</li><li class="_21Ahn-">20 length settings</li><li class="_21Ahn-">Gender: Men</li><li class="_21Ahn-">For Beard &amp; Moustache</li></ul>
"""

# data=pd.read_html(data)
# data1 = pd.read_html(data1)

# print({key:value for key, value in data[0].to_dict("split")["data"]})
    

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


print(ul_to_dict(data1))
