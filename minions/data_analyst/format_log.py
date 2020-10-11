#!/usr/bin/env python
# coding: utf-8
"""
日志格式化脚本
将日志文件按照正则表达式匹配生成以'\\t'分隔的格式化数据文件

Authors: hatlonely(hatlonely@gmail.com)
Date: 2014-12-05
"""

import re
import argparse
import sys


def WARNING(message):
    sys.stderr.write('WARNING: [%s] %s\n' % (
        time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())), message))


def process(regex, input='stdin', output='stdout'):
    if output == 'stdout':
        ofs = sys.stdout
    else:
        ofs = open(output, 'w')
    if input == 'stdin':
        ifs = sys.stdin
    else:
        ifs = open(input, 'r')

    pattern = re.compile(regex)
    for line in ifs:
        match = pattern.match(line)
        if not match:
            continue
        ofs.write('\t'.join(match.groups()))
        ofs.write('\n')


__command_example = """
command example:
    python format_log.py \\
            --input data.log \\
            --regex "key0:(\w) key1:(\d+) key2:(\d+)"
"""


def __parser():
    parser = argparse.ArgumentParser(description='format_log.py 1.0.0', usage=__command_example)
    parser.add_argument('-i', '--input', required='stdin', help='输入文件')
    parser.add_argument('-o', '--output', default='stdout', help='输出文件')
    parser.add_argument('-r', '--regex', required=True, help='匹配的正则, 需要提取的字段在"()"中')
    return parser


def main():
    options = __parser().parse_args(sys.argv[1:])
    process(options.regex, options.input, options.output)


if __name__ == '__main__':
    main()
