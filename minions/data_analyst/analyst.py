#!/usr/bin/env python
# coding: utf-8
"""
数据分析脚本
支持分析最大值，最小值，平均值，分位数

Authors: hatlonely(hatlonely@gmail.com)
Date: 2014-12-05
"""


import argparse
import sys
import re
import commands
import time


def WARNING(message):
    sys.stderr.write('WARNING: [%s] %s\n' % (
        time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())), message))


def fields_parse(index, fields, input):
    """ 字段解析
    
    Args:
        index: int 要统计分析的字段下标，从0开始
        fields: 要输出的字段，支持max, min, avg, count, total, 0.8, 0.9等分位数
        input: 输入文件

    Returns:
    return (per_str, percent, result)
        per_str: 字段名列表
        percent: 字段的值所在的行数
        result: 各个字段的值在row中的位置，其中每一个元素都是一个3元tuple
            如：('max', 0, 'peak_time')，表示取max行中的第0个字段当做peak_time的值
    """
    result  = list()
    per_str = list()
    percent = list()
    fields  = map(lambda x: x.strip(), fields.split(','))
    for field in fields:
        match = re.match(r'^((.+?)(_(\d+)){0,1})(\((\w*)\)){0,1}$', field)
        if not match:
            WARNING('invalid fields [{field}]'.format(field=field))
        group = match.groups()
        if re.match(r'\d+\.\d+', group[1]):
            per_str.append(group[1])

        if group[3] is None:
            idx = int(index)
        else:
            idx = int(group[3])

        if group[5] is None:
            name = group[0]
        else:
            name = group[5]

        result.append((group[1], idx, name))
    per_str = list(set(per_str))
    per_str.sort(key=float)
    percent = map(lambda x: float(x), per_str)

    # 计算文件行数 wc -l input
    (status, output) = commands.getstatusoutput('wc -l {input}'.format(input=input))
    if status != 0:
        WARNING("wc -l {input} failed")
        return None
    count = int(output.strip().split()[0])
    percent = map(lambda x: int(x * count), percent)

    # percent为per_str中的字段所在文件中的行数
    percent = [1,] + percent + [count, ]
    per_str = ['min', ] + per_str + ['max', ]
    return (per_str, percent, result)


def process(index, fields, input, output='stdout'):
    """ 分析过程

    Args:
        index: int 要统计分析的字段下标，从0开始
        fields: 要输出的字段，支持max, min, avg, count, total, 0.8, 0.9等分位数
        input: 输入文件
        output: 输出文件，默认输出到标准输出
    """
    (per_str, percent, fields) = fields_parse(index, fields, input)
    if output == 'stdout':
        ofs = sys.stdout
    else:
        ofs = open(output, 'w')

    # 对文件按照index字段排序，index从0开始，sort -k{index + 1}n input
    # 输出到input.sort中
    (status, output) = commands.getstatusoutput(
            'sort -k{index}n {input} > {input}.sort'.format(index=int(index) + 1, input=input))
    if status != 0:
        WARNING('sort -k{index}n {input} > {input}.sort failed'.format(index=int(index) + 1, input=input))

    count = 0
    total = 0
    pidx  = 0
    percent_row_map = {}
    for line in open('{input}.sort'.format(input=input)):
        count += 1
        row = line.strip().split('\t')
        total += int(row[index])
        while count == percent[pidx]:
            percent_row_map[per_str[pidx]] = row
            pidx += 1
            if pidx >= len(percent):
                break;

    for field in fields:
        if field[0] == 'count':
            ofs.write('{0}\t{1}\n'.format(field[2], count))
        elif field[0] == 'total':
            ofs.write('{0}\t{1}\n'.format(field[2], total))
        elif field[0] == 'avg':
            ofs.write('{0}\t{1}\n'.format(field[2], total / count))
        else:
            ofs.write('{0}\t{1}\n'.format(field[2], percent_row_map[field[0]][field[1]]))

    # 删除临时文件input.sort文件
    (status, output) = commands.getstatusoutput('rm -rf {input}.sort'.format(input=input))
    if status != 0:
        WARNING('rm -rf {input}.sort failed'.format(input=input))


__command_example = """
command example:
    python analyst.py \\
            --fields "max, min, avg, 0.8, 0.9" \\
            --index 2 \\
            --input in.dt \\
            --output out.tb

    python analyst.py \\
            --fields "max_0(key1), min, avg, 0.8_1(eighty_1), 0.9" \\
            --index 2 \\
            --input in.dt \\
            --output out.tb
"""


def __parser():
    parser = argparse.ArgumentParser(description='analyst.py 1.0.0', usage=__command_example)
    parser.add_argument('-i', '--input', default='stdin', help='输入文件')
    parser.add_argument('-o', '--output', default='stdout', help='输出文件')
    parser.add_argument('-f', '--fields', default='max, min, avg, 0.8, 0.9, 0.95, 0.99, 0.999', 
            help='输出的字段，格式为<field>[_index][(name)]，如：max_0(peak_time)表示最大值出现时的时间')
    parser.add_argument('-n', '--index', required=True, help='要统计的字段下标')
    return parser


def main():
    options = __parser().parse_args(sys.argv[1:])
    process(int(options.index), options.fields, options.input, options.output)


if __name__ == '__main__':
    main()
