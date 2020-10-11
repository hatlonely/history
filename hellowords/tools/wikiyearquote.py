#!/usr/bin/env python
# coding: utf-8

import httplib2
import pyquery
import sys
reload(sys)
sys.setdefaultencoding("utf8")
http = httplib2.Http(".cache")

out = open("../data/wikiquote.txt", "w")
headers = {
    "User-Agent":"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36",
    "Accept-Language": "zh-CN"
}

quotes = []
for i in range(1, 13):
    url = "https://zh.wikiquote.org/wiki/Wikiquote:%E6%AF%8F%E6%97%A5%E5%90%8D%E8%A8%80/{0}%E6%9C%88".format(i)
    response, content = http.request(url, "GET", headers=headers)

    jquery = pyquery.PyQuery(content)

    for quote in jquery('#mw-content-text').items('p'):
        if quote.text().strip() == '':
            continue
        if quote.text().strip().startswith('1月'):
            continue
        quotes.append(quote.text())

for quote in quotes:
    out.write("{0}\n".format(quote))

out.close()
