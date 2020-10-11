#!/usr/bin/env python3

import subprocess
import datetime
import sys
import re
import os
import argparse


class MTechStat(object):
    @staticmethod
    def git_stat(dt=None):
        # 获取 git 统计信息
        cmd = 'git log'
        args = ['--pretty=tformat:"commit\t%H\t%an\t%ct"', '--numstat']
        if dt is not None:
            args.append('--since={}'.format(dt))
        status, gitlog = subprocess.getstatusoutput('{} {}'.format(cmd, ' '.join(args)))
        if status != 0:
            sys.stderr.write('execute [{} {}] faild. output [{}]\n'.format(cmd, ' '.join(args), gitlog))
            return

        # 获取 git 项目地址
        cmd = 'git remote -v | grep origin | grep fetch | awk \'{print $2}\''
        status, remote = subprocess.getstatusoutput(cmd)
        if status != 0:
            sys.stderr.write('execute [{}] failed. output [{}]\n'.format(cmd, remote))

        infos = re.split('[:/]', remote)

        obj = {}
        total_change = 0
        objs = []
        for line in gitlog.split('\n'):
            values = line.split('\t')
            if len(values) == 4 and values[0] == 'commit':
                # 有些人提交了一些开源库(开源库本不应该提交), 影响统计, 这里做一个粗略地过滤, 一次提交不应该超过2000行
                if total_change < 2000:
                    for obj in objs:
                        yield 'mstat', 'mcode', '{}_{}'.format(obj['@commit'], obj['@file']), obj
                total_change = 0
                objs = []
                obj = {
                    '@timestamp': datetime.datetime.fromtimestamp(int(values[3]))-datetime.timedelta(hours=8),
                    '@weekday': datetime.datetime.fromtimestamp(int(values[3])).weekday(),
                    '@user': values[2],
                    '@remote': remote.split('@')[-1],
                    '@team': infos[-2],
                    '@proj': infos[-1].split('.')[0],
                    '@commit': values[1],
                    '@type': 'unknown',
                    '@lang': 'unknown',
                    '@file': '',
                    'insert': 0,
                    'delete': 0,
                    'change': 0,
                }

            if len(values) == 3:
                obj['@file'] = values[2]
                modfile = values[2]
                if modfile.endswith('"') or modfile.endswith('}'):
                    modfile = modfile[:-1]
                obj['@type'] = os.path.splitext(modfile)[1][1:]
                if obj['@type'] not in {'sh', 'go', 'java', 'cpp', 'c', 'cc', 'h', 'md', 'xml', 'conf', 'json', 'yaml',
                                        'scala', 'py', 'php', 'js', 'html', 'css', 'txt'}:
                    obj['@lang'] = 'unknown'
                else:
                    obj['@lang'] = obj['@type']
                    if obj['@lang'] in {'c', 'cc', 'cpp', 'h'}:
                        obj['@lang'] = 'c++'
                    if obj['@lang'] in {'conf', 'xml', 'json', 'yaml'}:
                        obj['@lang'] = 'conf'
                if values[0] != '-':
                    obj['insert'] = int(values[0])
                if values[1] != '-':
                    obj['delete'] = int(values[1])
                obj['change'] = obj['insert'] + obj['delete']
                total_change += obj['change']
                objs.append(obj.copy())

        if total_change < 2000:
            for obj in objs:
                yield 'mstat', 'mcode', '{}_{}'.format(obj['@commit'], obj['@file']), obj


def main():
    parser = argparse.ArgumentParser(description='技术统计')
    parser.add_argument('-s', '--since', help='开始时间，eg: [1.day.ago]')
    args = parser.parse_args()
    for obj in MTechStat.git_stat(args.since):
        print(obj.__repr__())


if __name__ == '__main__':
    main()
