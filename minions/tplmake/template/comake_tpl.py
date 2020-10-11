#!/usr/bin/env python
#coding: utf-8

""" comake模板

Author: hatloney(hatlonely@gmail.com)
Date: 2014-10-17
"""

import argparse


comake_prj_tpl = """#edit-mode: -*- python -*-
#coding:gbk

#工作路径.
WORKROOT('{workroot}')

#使用硬链接copy.
CopyUsingHardLink(True)

#C预处理器参数.
CPPFLAGS('-D_GNU_SOURCE -D__STDC_LIMIT_MACROS')

#C编译参数.
CFLAGS('-g -pipe -W -Wall -fPIC')

#C++编译参数.
CXXFLAGS('-g -pipe -W -Wall -fPIC')

#IDL编译参数
IDLFLAGS('--compack')

#UBRPC编译参数
UBRPCFLAGS('--compack')

#头文件路径.
INCPATHS('. ./include ./output ./output/include ../{common}/include/')

#链接参数.
LDFLAGS('-lpthread -lcrypto -lrt')

#依赖模块
#ImportConfigsFrom('../')

common_sources = GLOB(' ../{common}/src/*.cc ../{common}/src/*.cpp ')
user_sources = GLOB(' ./src/*.cpp ')
user_sources = user_sources + ' ' + common_sources

#可执行文件
Application('{executable}', Sources(user_sources))

TARGET(
    '.output_all',
    Prefixes('{executable}'),
    ShellCommands(
        'touch .output_all',
        'mkdir -p ./bin',
        'mkdir -p output/log',
        'mkdir -p output/conf',
        'mv {executable} ./bin',
        'cp ./conf/{conf} output/conf'
    ),
    CleanCommands(
        'rm -rf output',
        'rm -rf log',
        'rm -rf bin',
        'rm -rf .output_all'
    )
)
"""

comake_test_tpl = """#edit-mode: -*- python -*-
#coding:gbk

#工作路径.
WORKROOT('../{workroot}')

#使用硬链接copy.
CopyUsingHardLink(True)

#C预处理器参数.
CPPFLAGS('-D_GNU_SOURCE -D__STDC_LIMIT_MACROS ' +
        ' -Dprivate=public ' +
        ' -Dprotected=public ')

#C编译参数.
CFLAGS('-g -pipe -W -Wall -fPIC')

#C++编译参数.
CXXFLAGS('-g -pipe -W -Wall -fPIC')

#IDL编译参数
IDLFLAGS('--compack')

#UBRPC编译参数
UBRPCFLAGS('--compack')

#头文件路径.
INCPATHS('.. ../include ../output ../output/include ../../{common}/include/')

#链接参数.
LDFLAGS('-lpthread -lcrypto -lrt')

#依赖模块
ImportConfigsFrom('../')
CONFIGS('third-64/gtest@gtest_1-6-0-100_PD_BL')

common_sources = GLOB(' ../../{common}/src/*.cc ../../{common}/src/*.cpp ')

test_{executable} = common_sources + ' test_{executable}.cpp'

#可执行文件
Application('test_{executable}', Sources(test_{executable}))

TARGET(
    '.output_all',
    Prefixes('test_{executable}'),
    ShellCommands(
        'touch .output_all',
        'mkdir -p ./bin',
        'mkdir -p ./conf',
        'mkdir -p ./log',
        'mv test_{executable} ./bin',
        'cp ../conf/{conf} ./conf',
        'mkdir -p output/log',
        'mkdir -p output/conf',
        'cp ./conf/{conf} ./output/conf'
    ),
    CleanCommands(
        'rm -rf output',
        'rm -rf log',
        'rm -rf conf',
        'rm -rf bin',
        'rm -rf .output_all'
    )
)
"""

default_arguments = {
    'workroot': '../../../../../../',
    'executable': 'executable',
    'common': 'common',
    'conf': 'executable.conf',
    'type': 'exe',
}

__tpl_type = default_arguments['type']
__params = {}


command_example = """
command example:
    tplmake.py -t comake -t exe -e atom-idword -c idword.conf -m atom-common
    tplmake.py -t comake -t test -e idword_server -c idword.conf -m atom-common
"""


def parser():
    parser = argparse.ArgumentParser(usage=command_example)
    parser.add_argument('-t', '--type', default=default_arguments['type'],
            help='type(exe, lib, test), default "{0}"'.format(default_arguments['type']));
    parser.add_argument('-e', '--executable', default=default_arguments['executable'],
            help='executable binary output file, default "{0}"'.format(default_arguments['executable']));
    parser.add_argument('-w', '--workroot', default=default_arguments['workroot'],
            help='workroot, default "{0}"'.format(default_arguments['workroot']));
    parser.add_argument('-m', '--common', default=default_arguments['common'],
            help='common directory, default "{0}"'.format(default_arguments['common']));
    parser.add_argument('-c', '--conf', default=default_arguments['conf'],
            help='conf file, default "{0}"'.format(default_arguments['conf']));
    return parser


def params(options):
    global __tpl_type
    global __params
    args = parser().parse_args(options)
    __tpl_type = args.type
    __params = args.__dict__

    return __params;


def tpls():
    if __tpl_type == 'exe':
        return [comake_prj_tpl]
    elif __tpl_type == 'test':
        return [comake_test_tpl]
    else:
        return [comake_prj_tpl]


def outs():
    return ['COMAKE']
