#!/usr/bin/env python
# coding: utf-8
"""
这个脚本随机生成一些词，词来自于datas目录

Authors: hatlonely(hatlonely@gmail.com)
Date: 2015-02-06
"""

import sys
import random
import os
import argparse


def __get_filenames():
    filenames = []
    for filename in os.listdir(sys.path[0] + '/datas'):
        filenames.append(filename)
    return filenames


def __get_data_map():
    data_map = {}
    for filename in os.listdir(sys.path[0] + '/datas'):
        data_map[filename] = open(sys.path[0] + '/datas/' + filename).read().strip().split('\n')
    return data_map


def rand_data(datas='', number=1):
    rand_datas = []
    filenames = __get_filenames()
    data_map = __get_data_map()
    for i in range(0, number):
        if datas == '':
            data = random.choice(filenames)
        else:
            data = random.choice(datas.strip().split(','))
        rand_datas.append(random.choice(data_map[data]))
    return list(set(rand_datas))


__command_example = """
rand.py --list 1
rand.py --datas word,movie --number 10
"""


def __parser():
    parser = argparse.ArgumentParser(description='rand.py', usage=__command_example)
    parser.add_argument('-d', '--datas', default='', help='random datas')
    parser.add_argument('-l', '--list', default=False, type=bool, help='list available datas')
    parser.add_argument('-n', '--number', default=1, type=int, help='number')
    return parser


def main():
    options = __parser().parse_args(sys.argv[1:])
    if options.list:
        print ', '.join(__get_filenames())
    else:
        print '\n'.join(rand_data(options.datas, options.number))


if __name__ == '__main__':
    main()
