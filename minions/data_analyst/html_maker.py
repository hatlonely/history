#!/usr/bin/env python
# coding: utf-8
"""
将html片段拼成一个html文件

Authors: hatlonely(hatlonely@gmail.com)
Date: 2014-12-06
"""

import sys
import argparse


html = """<!DOCTYPE>
<html>
<head>
<meta charset="utf-8">
{styles}
</head>
<body>
{divs}
</body>
</html>
"""


def process(style, div, output='stdout'):
    if output == 'stdout':
        ofs = sys.stdout
    else:
        ofs = open(output, 'w')

    styles = ''
    for s in map(lambda x: x.strip(), style.split(',')):
        styles += '    <style type="text/css">'
        styles += open(s).read()
        styles += '    </style>'

    divs = ''
    for d in map(lambda x: x.strip(), div.split(',')):
        divs += '    <br/>'
        divs += '    <div>'
        divs += open(d).read()
        divs += '    </div>'

    ofs.write(html.format(styles=styles, divs=divs))


__command_example = """
command example:
    python html_maker.py \\
            --style "style.css" \\
            --div "table.div"

    python html_maker.py \\
            --style "style.css" \\
            --div "aaa.div, bbb.div" \\
            --output out.html
"""


def __parser():
    parser = argparse.ArgumentParser(usage=__command_example)
    parser.add_argument('-s', '--style', default=sys.path[0] + '/style.css', help='样式文件')
    parser.add_argument('-d', '--div', required=True, help='嵌入的div文件')
    parser.add_argument('-o', '--output', default='stdout', help='输出的文件，html格式')
    return parser


def main():
    options = __parser().parse_args(sys.argv[1:])
    process(options.style, options.div, options.output)


if __name__ == '__main__':
    main()
