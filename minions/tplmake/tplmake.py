#!/usr/bin/env python
#coding: utf-8

""" 模板生成工具
    模板工具存在template包中，以{tpl_name}_tpl.py命名
    {tpl_name}_tpl.py 必须实现如下三个函数
    tpls() 返回模板内的模板字符串列表
    outs() 返回模板输出的文件名列表
    params(options) 接受命令行参数，返回模板字符串所需的参数字典

Author: hatlonely(hatlonely@gmail.com)
Date: 2014-10-15
"""

import sys
import argparse


command_example = """
command example:
    tplmake.py -t cmakelists -h
    tplmake.py -t cppclass -h
    tplmake.py -t leetcode -h

    tplmake.py -t cmakelists -t exe -p PROJECT -e executable
    tplmake.py -t cppclass -c AB -n aa.bb
    tplmake.py -t leetcode -q "Two Sum"
"""


def parser():
    parser = argparse.ArgumentParser(description='tplmake.py 1.1.0', usage=command_example)
    parser.add_argument('-t', '--type', required=True,
            help='option value is one of (cmakelists, cppclass)');
    return parser


def main():
    args = parser().parse_args(sys.argv[1:3])
    arg_type = args.type.lower() + "_tpl"
    tpl = __import__("template." + arg_type, fromlist=[arg_type])
    
    params = tpl.params(sys.argv[3:])
    tpls = tpl.tpls()
    outs = tpl.outs()
    
    for i in range(0, len(tpls)):
        if outs[i] == 'stdout':
            print(tpls[i].format(**params))
        else:
            out = open(outs[i], 'w')
            out.write(tpls[i].format(**params))
            out.close()


if __name__ == '__main__':
    main()
