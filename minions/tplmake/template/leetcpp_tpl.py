#!/usr/bin/env python
#coding: utf-8

""" leetcode 模板

Author: hatloney(hatlonely@gmail.com)
Date: 2014-10-21
"""

import argparse


cmakelists_tpl = """CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT({project})

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${{{project}_BINARY_DIR}}/bin)
SET(CMAKE_CXX_FLAGS "-g -pipe -W -Wall -fPIC")

INCLUDE_DIRECTORIES(".")

IF (class STREQUAL hl)
    ADD_DEFINITIONS(-DHL=1)
    SET(SRC_LIST main.cpp {filename}_hl.hpp)
ENDIF()
IF (class STREQUAL pj)
    ADD_DEFINITIONS(-DPJ=1)
    SET(SRC_LIST main.cpp {filename}_pj.hpp)
ENDIF()

ADD_EXECUTABLE({filename} ${{SRC_LIST}})
"""


main_tpl = """#include <cassert>
#include "{filename}.h"

class TestSolution {{
public:
    static void test() {{
        // TODO your test code
    }}

private:
    static Solution solution_;
}};

Solution TestSolution::solution_;

int main() {{
    TestSolution::test();

    return 0;
}}
"""


header_tpl = """#if defined HL
    #include "{filename}_hl.hpp"
#elif defined PJ
    #include "{filename}_pj.hpp"
#endif
"""


default_arguments = {
    'question': 'Two Sum',
}


__params = {}


command_example = """
command example:
    tplmake.py -t leetcode -q "Two Sum"
"""


def parser():
    parser = argparse.ArgumentParser(usage=command_example)
    parser.add_argument('-q', '--question', required=True,
            help='question name');
    return parser


def params(options):
    global __params
    args = parser().parse_args(options)
    __params['question'] = args.question
    __params['project'] = ''
    __params['filename'] = ''

    # "Two Sum" => "tow_sum"
    __params['filename'] = args.question.replace(' ', '_').lower()
    if __params['filename'].startswith('_'):
        __params['filename'] = __params['filename'][1:]
    __params['project'] = 'LEETCODE_' + __params['filename'].upper()

    return __params


def tpls():
    return [cmakelists_tpl, main_tpl, header_tpl]


def outs():
    return ['CMakeLists.txt', 'main.cpp', __params['filename'] + '.h']
