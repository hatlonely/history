#!/usr/bin/env python
#coding: utf-8

""" leetcode java模板

Author: hatloney(hatlonely@gmail.com)
Date: 2014-10-30
"""

import argparse
import re

leetcode_java_tpl = """import java.lang.reflect.Method;

public class Test {{
    private static Method method_;
    private static Class class_;

    private static void test_cases() throws Throwable {{
        // test_case(new Object[]{{/* arg1, arg2 */}}, /* expect */);
        // TODO add your case here
    }};

    private static void test_case(Object[] args, Object ret) throws Throwable {{
        {return_type} result = ({return_type}) method_.invoke(class_.newInstance(), args);
        {return_type} expect = ({return_type}) ret;
        try {{
            assert result.equals(expect);
        }} catch (AssertionError e) {{
{params_args}
            System.out.println("test case failed: ");
{println_args}
            System.out.println("    expect: " + expect);
            System.out.println("    result: " + result);
        }}
    }}

    @SuppressWarnings("unchecked")
    public static void test(Class c) throws Throwable {{
        class_ = c;
        method_ = c.getMethod("{function_name}", new Class[]{{{param_type_class}}});
        test_cases();
    }}

    public static void main(String[] args) throws Throwable {{
        if (args.length != 1) {{
            System.out.println("Usage: java -ea Test <package>");
            System.out.println("    eg: java -ea Test pj");
            System.out.println("    eg: java -ea Test hl");
            return;
        }}

        test(Class.forName(args[0] + ".Solution"));
    }}
}}
"""

default_arguments = {
    'function': 'return_type function_name(param_type param)',
}


__params = {}


command_example = """
command example:
    tplmake.py -t leetjava
"""


def parser():
    parser = argparse.ArgumentParser(usage=command_example)
    parser.add_argument('-f', '--function', default=default_arguments['function'],
            help='function');
    return parser


def params(options):
    global __params
    args = parser().parse_args(options)
    function = args.function
    m = re.match(r'(.*?) (\w+)\((.*?)\)', function)
    __params['return_type'] = m.groups()[0]
    __params['function_name'] = m.groups()[1]
    __params['params_args'] = ''
    __params['println_args'] = ''
    params = m.groups()[2].split(',')
    param_type_class_vec = []
    count = 0
    for param in params:
        ptype = param.split()[0]
        pname = param.split()[1]
        param_type_class_vec.append(ptype + '.class')
        __params['params_args'] += '            {type} {name} = ({type}) args[{idx}];\n'.format(type=ptype, name=pname, idx=count)
        __params['println_args'] += '            System.out.println("    {name}: " + args[{idx}]);\n'.format(name=pname, idx=count)
        count += 1
    __params['param_type_class'] = ', '.join(param_type_class_vec)
    __params['println_args'] = __params['println_args'][0:-1]
    __params['params_args'] = __params['params_args'][0:-1]
    return __params


def tpls():
    return [leetcode_java_tpl]


def outs():
    return ['Test.java']
