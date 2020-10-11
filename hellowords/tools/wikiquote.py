import httplib2
import pyquery
import sys
reload(sys)
sys.setdefaultencoding("utf8")
http = httplib2.Http(".cache")

out = open("../data/wikiquote.txt", "a")

url = "https://zh.wikiquote.org/wiki/Wikiquote:%E6%AF%8F%E6%97%A5%E5%90%8D%E8%A8%80"
response, content = http.request(url, "GET")
jquery = pyquery.PyQuery(content)
quote = jquery('#mw-content-text>center>div>p').text()
out.write("{0}\n".format(quote))
out.close()
