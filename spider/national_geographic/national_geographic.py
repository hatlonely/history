#!/usr/bin/env python
# coding: utf-8

"""
国家地理每日图片抓取脚本
用法：national_geographic.py <start_index> <end_index>
    start_index 为开始的下标，4为数
    end_index 为结束下标，4位数
该脚本会将start_index和end_index之间的图片下载到工作目录的images文件夹下
源：http://dili.bdatu.com/index.php/Share/index/id/dddd

Authors: hatlonely(hatlonely@gmail.com)
Date: 2015-06-18
"""

import sys
import urllib2
import re
import commands
import sys

image_regex = re.compile('<div class="pic" align="center">'
    '<img src="(.*?)"/ width="80%"></div>', re.M)

title_regex = re.compile('<title>(.*?)</title>', re.M)

def title_image(url_address, prefix):
    html = urllib2.urlopen(url_address).read()
    image = image_regex.findall(html)
    title = title_regex.findall(html)

    if len(image) == 0 or len(title) == 0:
        return ''
    return 'wget {1} -O "images/{2}_{0}.JPG"'.format(title[0], image[0], prefix)

def main():
    if len(sys.argv) != 3:
        print('usage: national_geographic.py <start_index> <end_index>')
    for i in range(int(sys.argv[1]), int(sys.argv[2])):
        command = title_image('http://dili.bdatu.com/index.php/Share/index/id/' + str(i), str(i))
        if command != '':
            (status, output) = commands.getstatusoutput(command)
            print command

if __name__ == '__main__':
    main()

