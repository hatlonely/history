#!/usr/bin/env python
# coding: utf-8
"""
数据统计分析脚本
以sql语法来分析格式化的文本文件
目前支持select，group by，where关键字
where条件只支持最多两个条件，支持and和or，不支持括号

Authors: hatlonely(hatlonely@gmail.com)
Date: 2014-12-05
"""

import argparse
import sys
import re
import time


def WARNING(message):
    sys.stderr.write('WARNING: [%s] %s\n' % (
        time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())), message))


def FATAL(message):
    sys.stderr.write('FATAL: [%s] %s\n' % (
        time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())), message))


def lower_than(x, y):
    return int(x) < int(y)
def great_than(x, y):
    return int(x) > int(y)
def equal(x, y):
    return x == y
def lower_equal(x, y):
    return int(x) <= int(y)
def great_equal(x, y):
    return int(x) >= int(y)
def sum(x, y):
    return int(x) + int(y)
def avg(x, y):
    return int(x) + int(y)
op_dict = {
    '<'   : lower_than,
    '>'   : great_than,
    '='   : equal,
    '=='  : equal,
    '<='  : lower_equal,
    '>='  : great_equal,
    'sum' : sum,
    'max' : max,
    'min' : min,
    'avg' : avg,
}


class Select(object):
    """ select 子句

    Attributes:
        columns: select各个字段的计算方法
        datas: select各个字段的值
        count: 当前group中有多少行
    """
    def __init__(self, table, condition):
        """
        columns中的结构有如下几种情况：
            tuple: (func, index[int])
                func为处理函数，在op_dict中，index为字段的下标，data为累计的值，存在self.datas中
                eg: max(value1) => (max, 1)
            str: "count"表示希望返回group中的行数，这个值与属性中的count值, count => "count"
            int: index字段的值，eg: value1 => 1

        Args:
            table: 字段名到下标的映射, eg: {key:0, value1: 1, value2: 2}
            condition: select子句, eg: "value1, sum(value2), count"
        """
        self.columns = list()
        self.datas = list()
        self.count = 0
        fields = map(lambda x: x.strip(), condition.split(','))
        for field in fields:
            m = re.match(r'^(\w+)(\((\w*)\)){0,1}$', field)
            if not m:
                WARNING("unknow function {field}".format(field=field))
                return None
            match = m.groups()
            if match[0] == 'count':
                self.columns.append(match[0])
            elif match[2] is not None:
                if re.match(r'^([0-9]+)$', match[2]):
                    self.columns.append((op_dict[match[0]], int(match[2].strip())))
                else:
                    self.columns.append((op_dict[match[0]], table[match[2].strip()]))
            elif match[1] is None:
                if re.match(r'^([0-9]+)$', match[0]):
                    self.columns.append(int(match[0].strip()))
                else:
                    self.columns.append(table[match[0].strip()])
        self.length = len(self.columns)
        for i in range(0, self.length):
            self.datas.append(0)

    def select(self, row):
        """ 处理行

        Args:
            row: 文件中的行分隔的字段
        """
        self.count += 1
        for i in range(0, self.length):
            if type(self.columns[i]) != tuple:
                continue
            self.datas[i] = self.columns[i][0](int(row[self.columns[i][1]]), self.datas[i])

    def get_datas(self):
        """ 获取datas中的数据
        对于count和avg需要再做一次处理

        Retruns:
            返回select中的各个字段
        """
        for i in range(0, self.length):
            if type(self.columns[i]) == int:
                pass
            elif type(self.columns[i]) == tuple:
                if self.columns[i][0] == avg:
                    self.datas[i] /= self.count
            elif type(self.columns[i]) == str:
                if self.columns[i] == 'count':
                    self.datas[i] = self.count
        return map(lambda x: str(x), self.datas)

    def update(self, row):
        """ 根据row更新datas中的各个字段

        Args:
            row: 文件中的行分隔的字段
        """
        for i in range(0, self.length):
            if type(self.columns[i]) == int:
                self.datas[i] = row[self.columns[i]]
            elif type(self.columns[i]) == str:
                pass
            else:
                self.datas[i] = int(row[self.columns[i][1]])
        self.count = 1


class Where(object):
    """ where子句

    Attribute:
        and_cond: and条件
        or_cond: or条件
    """
    def __init__(self, table, condition):
        """
        想把所有的条件都放到两个条件的list中，但是这里的实现是不对的！！！
        现在可以支持两个条件，不支持括号

        Args:
            table: 字段名到下标的映射, eg: {value1: 0, value2: 1}
            condition: where子句, eg: "value1 > 10 AND value2 < 20"
        """
        self.and_cond = list()
        self.or_cond = list()
        if condition == '':
            return
        cond = re.split('(and|or)', condition)
        self.and_cond.append(cond[0])
        for i in range(1, len(cond), 2):
            if cond[i] == 'and':
                self.and_cond.append(cond[i + 1])
            elif cond[i] == 'or':
                self.or_cond.append(cond[i + 1])
        self.and_cond = map(
                lambda x: map(lambda y: y.strip(), re.split('(>|<|>=|<=|==)', x)),
                self.and_cond)
        self.or_cond = map(
                lambda x: map(lambda y: y.strip(), re.split('(>|<|>=|<=|==)', x)),
                self.or_cond)
        for a in self.and_cond:
            if re.match(r'^([0-9]+)$', a[0]):
                a[0] = int(a[0])
            else:
                a[0] = table[a[0]]
            a[1] = op_dict[a[1]]
        for o in self.or_cond:
            if re.match(r'^([0-9]+)$', a[0]):
                a[0] = int(a[0])
            else:
                o[0] = table[o[0]]
            o[1] = op_dict[o[1]]

    def where(self, row):
        """ 判断该行是否应该被过滤
        
        Args:
            row: 文件中的行分隔的字段

        Returns:
            True: 满足过滤条件
            False: 不满足过滤条件
        """
        for cond in self.and_cond:
            if not cond[1](row[cond[0]], cond[2]):
                return False
        for cond in self.or_cond:
            if cond[1](row[cond[0]], cond[2]):
                return True
        return True


class GroupBy(object):
    """ group by 子句

    Attribute:
        group: group by字段的下标集合
        length: group的长度
        values: group by字段的值
    """
    def __init__(self, table, condition):
        """ 将要group by的字段的下标存在group中

        Args:
            table: 字段名到下标的映射, eg: {value1: 0, value2: 1}
            condition: group子句, eg: "key1, key2"
        """
        if condition == '':
            self.group = list()
            self.values = list()
            self.length = 0
            return
        self.group = map(lambda x: x.strip(), condition.split(','))
        for i in range(0, len(self.group)):
            if re.match(r'^([0-9]+)$', self.group[i]):
                self.group[i] = int(self.group[i])
            else:
                self.group[i] = table[self.group[i]]
        self.length = len(self.group)
        self.values = map(lambda x: 0, self.group)

    def group_by(self, row):
        """ 根据group中的字段，用values中的值和row中的值比较

        Args:
            row: 文件中的行分隔的字段

        Returns:
            True: values中的值与row中的值一致，在同一个group中
            False: values中的值与row中的值不同，在不同的group中
        """
        if self.length == 0:
            return False
        for i in range(0, self.length):
            if self.values[i] != row[self.group[i]]:
                return False
        return True

    def update(self, row):
        """ 根据row中的值更新values中的值
        """
        for i in range(0, self.length):
            self.values[i] = row[self.group[i]]


def query_parse(table, query):
    """ sql解析

    Args:
        table [str]: 输入文件各个字段的含义
                eg: "key, value1, value2, vlaue3" 
        query [str]: sql语句
                eg: "SELECT key, max(value1), min(value2), count, sum(value3) GROUP BY key WHERE value3 > 90"
    Returns:
        {select: Select(), group: GroupBy(),  where: Where()}
    """
    fields = list()
    if table.strip() != '':
        fields = map(lambda x: x.strip(), table.split(','))
    fields_int_dict = dict()
    for i in range(0, len(fields)):
        # fields_int_dict: {"key": 0, "value1": 1, "vaule2": 2, "value3": 3}
        fields_int_dict[fields[i]] = i

    query = query.lower()
    indexs = list()
    indexs.append(query.find('select'))
    indexs.append(query.find('group'))
    indexs.append(query.find('where'))
    indexs.append(len(query))
    indexs = filter(lambda x: x != -1, indexs)
    subs = list()
    for i in range(0, len(indexs) - 1):
        subs.append(query[indexs[i]:indexs[i + 1]])
    result = dict()
    result['group'] = GroupBy(fields_int_dict, '')
    result['where'] = Where(fields_int_dict, '')
    for sub in subs:
        if sub.startswith('select'):
            # eg: Select(fields_int_dict, "key, max(value1), min(value2), count, sum(value3)")
            result['select'] = Select(fields_int_dict, sub[len('select'):].strip())
        elif sub.startswith('group'):
            # eg: GroupBy(fields_int_dict, "key")
            result['group'] = GroupBy(fields_int_dict, sub[len('group by'):].strip())
        elif sub.startswith('where'):
            # eg: Where(fields_int_dict, "value3 > 90 AND value2 > 90")
            result['where'] = Where(fields_int_dict, sub[len('where'):].strip())
    return result


def process(query, table, input='stdin', output='stdout'):
    """ 处理过程

    Args:
        table: 各个字段的含义
        query: sql语句
        input: 输入文件名，默认标准输入
        output: 输出文件名，默认标准输出
    """
    result = query_parse(table, query)
    select = result['select']
    group  = result['group']
    where  = result['where']

    # 直接输出的字段必须是group by中的字段，或者不指定group by直接输出
    if len(group.group) != 0:
        for column in select.columns:
            if type(column) == int and group.group.count(column) == 0:
                WARNING("select fields not in group by.")

    if output == 'stdout':
        ofs = sys.stdout
    else:
        ofs = open(output, 'w')
    if input == 'stdin':
        ifs = sys.stdin
    else:
        ifs = open(input, 'r')

    line = ifs.readline()
    row  = line.strip().split('\t')
    while not where.where(row):
        line = ifs.readline()
        row  = line.strip().split('\t')
    group.update(row)
    select.update(row)
    while True:
        line = ifs.readline()
        # 文件结束
        if line == '':
            break
        row = line.strip().split('\t')
        # 过滤不满足条件的行
        if not where.where(row):
            continue
        # 同一组的值，计算
        if group.group_by(row):
            select.select(row)
        # 不同组的值，输出
        else:
            ofs.write('\t'.join(select.get_datas()))
            ofs.write('\n')
            group.update(row)
            select.update(row)
    ofs.write('\t'.join(select.get_datas()))
    ofs.write('\n')
    ofs.close()


__command_example="""
command example:
    python select.py \\
            --table "key, value1, value2, value3" \\
            --query "SELECT key, max(value1), min(value2), count, sum(value3) GROUP BY key WHERE value3 > 90 AND value2 > 90"

    python select.py \\
            --query "SELECT 0, max(2), sum(3) group by 1 where 1 > 90"
"""


def __parser():
    parser = argparse.ArgumentParser(description='select.py 1.0.0', usage=__command_example)
    parser.add_argument('-i', '--input', default='stdin', help='输入文件')
    parser.add_argument('-o', '--output', default='stdout', help='输出文件')
    parser.add_argument('-t', '--table', default='', help='table的格式，以\',\'分隔')
    parser.add_argument('-q', '--query', required=True, help='query语句')
    return parser


def main():
    options = __parser().parse_args(sys.argv[1:])
    process(options.query, options.table, options.input, options.output)


if __name__ == '__main__':
    main()
