#!/usr/bin/env python
#coding: utf-8

""" c++ class模板

Author: hatloney(hatlonely@gmail.com)
Date: 2014-10-15
"""

import argparse
import re
import time


header_tpl = """// @file {file}.h
// @desc {description}
// @auth {author}({email})
// @vers {version}
// @date {date}

#pragma once

{namespace_start}

class {class_name} {{
public:
    explicit {class_name}() = default;
    virtual ~{class_name} = default;
    {class_name}& operator=(const {class_name}&) = default;
    {class_name}(const {class_name}&) = default;

private:

}};

{namespace_end}
"""

source_tpl = """// @file {file}.cpp
// @desc {description}
// @auth {author}({email})
// @vers {version}
// @date {date}

{namespace_start}

{namespace_end}
"""

default_arguments = {
    'class_name': '',
    'namespace': '',
    'author': 'hatlonely',
    'email': 'hatlonely@gmail.com',
    'version': '1.0',
    'description': '',
}

__params = {}


command_example = """
command example:
    tplmake.py -t cppclass -c AB -n aa.bb
    tplmake.py -t cppclass -c AB -n aa.bb -d 'example class AB'
"""


def parser():
    parser = argparse.ArgumentParser(usage=command_example)
    parser.add_argument('-c', '--class-name', required=True,
            help='class name, this argument is required');
    parser.add_argument('-n', '--namespace', default=default_arguments['namespace'],
            help='namespace for class, strong recommanded add this argument');
    parser.add_argument('-a', '--author', default=default_arguments['author'],
            help='your name, default "{0}"'.format(default_arguments['author']));
    parser.add_argument('-e', '--email', default=default_arguments['email'],
            help='your email address, default "{0}"'.format(default_arguments['email']));
    parser.add_argument('-v', '--version', default=default_arguments['version'],
            help='class version, default "{0}"'.format(default_arguments["version"]));
    parser.add_argument('-d', '--description', default=default_arguments['description'],
            help='description for the class, default nothing');
    return parser


def params(options):
    args = parser().parse_args(options)
    __params['class_name'] = args.class_name
    __params['author'] = args.author
    __params['email'] = args.email
    __params['version'] = args.version
    __params['description'] = args.description

    __params['date'] = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
    __params['namespace_start'] = '\n'
    __params['namespace_end'] = '\n'

    # 类名转成文件名：AB => a_b
    pattern = re.compile('([A-Z])')
    __params['file'] = pattern.sub(r'_\1', args.class_name).lower()
    if __params['file'].startswith('_'):
        __params['file'] = __params['file'][1:]

    # 命名空间
    namespace = args.namespace.strip()
    __params['namespace_start'] = '\n'
    __params['namespace_end'] = '\n'
    names = namespace.split('.')
    for name in names:
        if name == '':
            break
        __params['namespace_start'] = __params['namespace_start'] + 'namespace {0} {{\n'.format(name)
        __params['namespace_end'] = '\n}}  // namespace {0}'.format(name) + __params['namespace_end']
    __params['namespace_start'] = __params['namespace_start'][1:-1]
    __params['namespace_end'] = __params['namespace_end'][1:-1]

    return __params


def tpls():
    return [header_tpl, source_tpl]


def outs():
    return [__params['file'] + '.h', __params['file'] + '.cpp']
