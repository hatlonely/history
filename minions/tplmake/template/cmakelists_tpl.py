#!/usr/bin/env python
#coding: utf-8

""" CMakeLists.txt模板

Author: hatloney(hatlonely@gmail.com)
Date: 2014-10-15
"""

import argparse


cm_exe_tpl = """CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT({project})

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${{PROJECT_BINARY_DIR}}/bin)
SET(CMAKE_CXX_FLAGS "{cxx_flags}")
SET(WORK_ROOT "{lib_base_path}")

AUX_SOURCE_DIRECTORY(src SOURCES)
SET(SRC_LIST ${{SOURCES}})

INCLUDE_DIRECTORIES(
    "./include"
{include_dirs}
)

LINK_DIRECTORIES(
{link_dirs}
)

ADD_DEFINITIONS(
)

ADD_EXECUTABLE({executable} ${{SRC_LIST}})

TARGET_LINK_LIBRARIES({executable}
)

ADD_CUSTOM_COMMAND(
    TARGET {executable}
    POST_BUILD
    COMMAND echo "${{{project}_SOURCE_DIR}}"
    COMMAND echo "${{{project}_BINARY_DIR}}"
)
"""

cm_lib_tpl = """CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT({project})

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(LIBRARY_OUTPUT_PATH ${{{project}_BINARY_DIR}}/lib)
SET(CMAKE_CXX_FLAGS "{cxx_flags}")
SET(WORK_ROOT "{lib_base_path}")

AUX_SOURCE_DIRECTORY(src SOURCES)
SET(SRC_LIST ${{SOURCES}})

INCLUDE_DIRECTORIES(
    "./include"
{include_dirs}
)

ADD_LIBRARY({executable} ${{SRC_LIST}})

ADD_CUSTOM_COMMAND(
    TARGET {executable}
    POST_BUILD
    COMMAND mkdir -p output
    COMMAND cp -r ${{{project}_SOURCE_DIR}}/include output
    COMMAND cp -r lib output
)
"""

cm_test_tpl = """CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT({project})

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${{{project}_BINARY_DIR}}/bin)
SET(CMAKE_CXX_FLAGS "{cxx_flags}")
SET(WORK_ROOT "{lib_base_path}")

AUX_SOURCE_DIRECTORY(../src SOURCES)
AUX_SOURCE_DIRECTORY(. TEST_SOURCES)
SET(SRC_LIST ${{SOURCES}} ${{TEST_SOURCES}})

INCLUDE_DIRECTORIES(
    "../include"
{include_dirs}
)

LINK_DIRECTORIES(
{link_dirs}
)

ADD_DEFINITIONS(
    -Dprivate=public
    -Dproctect=public
    -DGTEST_USE_OWN_TR1_TUPLE=1
)

ADD_EXECUTABLE({executable} ${{SRC_LIST}})

TARGET_LINK_LIBRARIES({executable}
)

ADD_CUSTOM_COMMAND(
    TARGET {executable}
    POST_BUILD
    COMMAND echo "${{{project}_SOURCE_DIR}}"
    COMMAND echo "${{{project}_BINARY_DIR}}"
)
"""

libs_map = {
    'boost': 'third/boost/boost-1.56.0',
    'gtest': 'google/gtest/gtest-1.6.0',
    'lh_configure': 'loadinghorizion/configure/configure-1.0.0'
}

default_arguments = {
    'project': 'PROJCET',
    'executable': 'executable',
    'cxx_flags': '-g -pipe -W -Wall -fPIC',
    'lib_base_path': '../../../..',
    'librarys': 'boost gtest',
    'type': 'exe',
}

__tpl_type = default_arguments['type']
__params = {}


command_example = """
command example:
    tplmake.py -t cmakelists -t exe -p PROJECT -e executable -l 'boost gtest'
    tplmake.py -t cmakelists -t lib -p PROJECT -e executable
    tplmake.py -t cmakelists -t test -p PROJECT -e executable
"""


def parser():
    parser = argparse.ArgumentParser(usage=command_example)
    parser.add_argument('-t', '--type', default=default_arguments['type'],
            help='type(exe, lib, test), default "{0}"'.format(default_arguments['type']));
    parser.add_argument('-p', '--project', default=default_arguments['project'],
            help='your project name, default "{0}"'.format(default_arguments['project']));
    parser.add_argument('-e', '--executable', default=default_arguments['executable'],
            help='your executable name, default "{0}"'.format(default_arguments['executable']));
    parser.add_argument('-f', '--cxx-flags', default=default_arguments['cxx_flags'],
            help='cxx flags, default "{0}"'.format(default_arguments['cxx_flags']));
    parser.add_argument('-b', '--lib-base-path', default=default_arguments['lib_base_path'],
            help='library base path, default "{0}"'.format(default_arguments['lib_base_path']));
    parser.add_argument('-l', '--librarys', default=default_arguments['librarys'],
            help='librarys, default "{0}"'.format(default_arguments['librarys']));
    return parser


def params(options):
    global __tpl_type
    global __params
    args = parser().parse_args(options)
    __tpl_type = args.type
    __params['project'] = args.project
    __params['executable'] = args.executable
    __params['cxx_flags'] = args.cxx_flags
    __params['include_dirs'] = '\n'
    __params['link_dirs'] = '\n'

    if __tpl_type == 'test':
        __params['lib_base_path'] = '../' + args.lib_base_path
    else:
        __params['lib_base_path'] = args.lib_base_path

    librarys = args.librarys.strip()
    libs = librarys.split()
    for lib in libs:
        if lib == '':
            break
        __params['include_dirs'] += '    "${{{0}_SOURCE_DIR}}/${{WORK_ROOT}}/{1}/include"\n'.format(__params['project'], libs_map[lib])
        __params['link_dirs'] += '    "${{{0}_SOURCE_DIR}}/${{WORK_ROOT}}/{1}/lib"\n'.format(__params['project'], libs_map[lib])
    __params['include_dirs'] = __params['include_dirs'][1:-1]
    __params['link_dirs'] = __params['link_dirs'][1:-1]

    return __params


def tpls():
    if __tpl_type == 'exe':
        return [cm_exe_tpl]
    elif __tpl_type == 'lib':
        return [cm_lib_tpl]
    elif __tpl_type == 'test':
        return [cm_test_tpl]
    else:
        return [cm_exe_tpl]


def outs():
    return ['CMakeLists.txt']
