#!/usr/bin/env python3
# 依赖: pip install murmurhash3
# 总空间大小为M的桶内，存放N个数据，那么这N个数据冲突数据的期望
# 对于这个问题这篇文章有详细的分析 https://leondong1993.github.io/2017/05/28/multi-bucket-hash/
# 这个脚本是针对这个问题模拟实际环境下的冲突量

import uuid
import mmh3
import datetime
import os
import sys
import random


m = 2 ** 64
n = 300000


def next_string():
    return '{}-package-{:03}'.format(uuid.uuid4(), random.randint(0, 999))


def hash_string(text):
    return mmh3.hash(text)


def save_to_file(filename):
    with open(filename, 'w') as fp:
        for _ in range(n):
            fp.write(next_string() + '\n')


def analysis():
    filename = "string_source.txt"
    keys = set()

    time_begin = datetime.datetime.now()

    if not os.path.exists(filename) or (len(sys.argv) > 1 and sys.argv[1] == '--save'):
        save_to_file(filename)

    for line in open(filename):
        keys.add(hash_string(line))

    print('M = {}'.format(m))
    print('N = {}'.format(n))
    print('E(X) = {}'.format(n - len(keys)))
    print('P = {}'.format(1 - len(keys) / n))
    print('time: {}s'.format((datetime.datetime.now() - time_begin).seconds))


def main():
    analysis()

if __name__ == '__main__':
    main()
