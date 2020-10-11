#!/usr/bin/env python
#encoding: utf-8
"""
构造测试数据
实际数据可用download.sh从服务器上抓取日志

Authors: hatlonely(hatlonely@gmail.com)
Date: 2014-12-06
"""

import random

names = ['Monkey-D-Luffy', 'Nami', 'Roronoa-Zoro', 'Usopp-Sogeking', 'Sanji', 'Tony-Tony-Chopper', 'Nico-Robin', 'Franky', 'Brook']

for i in range(0, 100):
    print('OnePiece: {0} funny[{1}], lovely[{2}], damage[{3}]'.format(names[random.randint(0, len(names) - 1)],
        random.randint(80, 100), random.randint(80, 100), random.randint(80, 100)))
