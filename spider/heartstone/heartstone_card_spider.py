#!/usr/bin/env python
# coding: utf-8

"""
炉石传说卡牌信息抓取脚本
输出格式：
   稀有度 | 名称 | 技能描述 | 职业 | 类型 | 法力 | 攻击 | 生命
源：http://db.duowan.com/lushi/card/list/

Authors: hatlonely(hatlonely@gmail.com)
Date: 2015-04-19
"""

import urllib2
import re

heartstone_url = 'http://db.duowan.com/lushi/card/list/'

# 下一页
next_page_regex = re.compile(r'<a target="_self" title="下一页" rel="next" href="(.*html)">下一页</a>', re.M)

# 卡牌信息
item_regex = re.compile(r'<tr>\s*'
    '<td class="name"><a([\s\S]*?)>(.*?)</a></td>\s*'   # 稀有度 | 名称
    '<td class="skill">[\s\S]*?</td>\s*'
    '<td class="txt">(.*?)</td>\s*'     # 技能描述
    '<td>(.*?)</td>\s*'                 # 职业
    '<td>(.*?)</td>\s*'                 # 类型
    '<td>(\d+)<img[\s\S]*?></td>\s*'    # 法力
    '<td>(\d+)<img[\s\S]*?></td>\s*'    # 攻击
    '<td>(\d+)<img[\s\S]*?></td>\s*'    # 生命
    '</tr>'
    , re.M)

# 稀有度，用颜色区分不同的稀有度，灵魂绑定卡牌没有这个属性
rarity_regex = re.compile(r'style="color:(#[0-9a-fA-F]+)"', re.M)

color_rarity_map = {
    '#008000': '普通',
    '#3366ff': '稀有',
    '#c600ff': '史诗',
    '#FF6600': '传说'
}

def main():
    current_url = heartstone_url
    while True:
        html = urllib2.urlopen(current_url).read()
        next_url = next_page_regex.findall(html)[0]
        items = item_regex.findall(html)
        for item in items:
            if len(item) == 8:
                raritys = rarity_regex.findall(item[0])
                if len(raritys) == 0:
                    print '灵魂绑定\t' + '\t'.join(item[1:])
                else:
                    print color_rarity_map[raritys[0]] + '\t' + '\t'.join(item[1:])
        if current_url == next_url:
            break
        current_url = next_url


if __name__ == '__main__':
    main()
