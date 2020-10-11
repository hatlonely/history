#!/usr/bin/env python3


import requests
import pyquery
from pyquery import PyQuery as pq

url = "http://www.yuzhiyue.com/cycd/Index.asp?Page={}&Sort1=&Sort2="

headers = {
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8",
    "Accept-Encoding": "gzip, deflate",
    "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8",
    "Cache-Control": "max-age=0",
    "Connection": "keep-alive",
    "Host": "www.yuzhiyue.com",
    "Referer": "http://www.yuzhiyue.com/cycd/Index.asp?Page=130&Sort1=&Sort2=",
    "Upgrade-Insecure-Requests": "1",
    "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36",
}


for i in range(1, 131):
    res = requests.get(url.format(i), headers=headers)
    q = pq(str(res.content, "GB18030"))
    for item in q("td.tdline").items():
        print(item.text())
