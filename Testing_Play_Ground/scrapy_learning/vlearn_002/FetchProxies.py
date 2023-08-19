from time import time
from bs4 import BeautifulSoup
import requests

print("Fetching.....", end="")


def GetProxys():
    website_html = requests.get("https://free-proxy-list.net").text
    soup = BeautifulSoup(website_html, "html.parser")
    soup = soup.find("table")
    Headings = [] 
    Body = []
    Ip = []
    for heading in soup.find_all("th"):
        Headings.append(heading.text)
    for ip_html in soup.find_all("tr"):
        ip_info_list = []
        for ip_info in ip_html.find_all("td"):
            ip_info_list.append(ip_info.text)
        if len(ip_info_list) > 1:
            if ip_info_list[6] == "yes":
                Ip.append(f"{ip_info_list[0]}:{ip_info_list[1]}")
                Body.append(ip_info_list)
    return Ip, Body

# while True:
Ips, info = GetProxys()
f = open("proxies.txt", "w")
f.write("\n".join(Ips))
f.close()
