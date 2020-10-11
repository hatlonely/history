#!/usr/bin/env python
# coding: utf-8
"""
将数据做成html表格
输入数据的每行的格式为key\tvalue

Authors: hatlonely(hatlonely@gmail.com)
Date: 2014-12-06
"""

import sys
import argparse
import re
import time
import sys


div = """    <table>
        <thead>
{table_title}
{table_head}
        </thead>
        <tbody>
{table_body}
        </tbody>
    </table>
"""


def WARNING(message):
    sys.stderr.write('WARNING: [%s] %s\n' % (
        time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())), message))


def process(fields, datas, title='', output='stdout'):
    if output == 'stdout':
        ofs = sys.stdout
    else:
        ofs = open(output, 'w')

    fields  = map(lambda x: x.strip(), fields.split(','))
    datas   = map(lambda x: x.strip(), datas.split(','))
    keys    = list()
    values  = list()
    columns = list()
    rows    = list()
    for field in fields:
        match = re.match(r'^(.*?)(\((.*?)\)){0,1}$', field)
        if not match:
            WARNING('unknow field [{field}]'.format(field=field))
        group = match.groups()
        keys.append(group[0])
        if group[2] is not None:
            columns.append(group[2])
        else:
            columns.append(group[0])

    for data in datas:
        match = re.match(r'^(.*?)(\((.*?)\)){0,1}$', data)
        if not match:
            WARNING('unknow data [{field}]'.format(field=field))
        group = match.groups()
        values.append(group[0])
        if group[2] is not None:
            rows.append(group[2])
        else:
            rows.append(group[0])
        
    indent = '            '
    table_head = indent + '<tr><th>#</th>'
    for column in columns:
        table_head += '<th>{column}</th>'.format(column=column)
    table_head += '</tr>'
    table_body = ''
    for i in range(0, len(values)):
        table_body += indent + '<tr>'
        table_body += '<th>{row}</th>'.format(row=rows[i])
        kvs = {}
        for line in open(values[i]):
            kv = map(lambda x: x.strip(), line.strip().split('\t'))
            kvs[kv[0]] = kv[1]
        for key in keys:
            table_body += '<td>{value}</td>'.format(value=kvs[key])
        table_body += '</tr>\n'
    table_body = table_body[:-1]
    table_title = '{indent}<th colspan="{cols}">{title}</th>'.format(indent=indent, title=title, cols=len(columns) + 1)
    ofs.write(div.format(table_head=table_head, table_body=table_body, table_title=table_title))


__command_example = """
command example:
    python table_maker.py \\
            --fields "max, min, avg, 0.8" \\
            --datas "aaa.tb, bbb.tb"

    python table_maker.py \\
            --fields "max, min, avg, 0.8" \\
            --datas "aaa.tb, bbb.tb" \\
            --output table.div
"""


def parser():
    parser = argparse.ArgumentParser(usage=__command_example)
    parser.add_argument('-f', '--fields', required=True, help='需要的字段列表')
    parser.add_argument('-d', '--datas', required=True, help='包含字段的文件名列表')
    parser.add_argument('-o', '--output', default='stdout', help='输出的文件，html格式')
    parser.add_argument('-t', '--title', default='', help='标题')
    return parser


def main():
    options = parser().parse_args(sys.argv[1:])
    process(options.fields, options.datas, options.title, options.output)


if __name__ == '__main__':
    main()

