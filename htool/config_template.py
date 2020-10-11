#!/usr/bin/env python3

import argparse
import json


def main():
    parser = argparse.ArgumentParser(description='配置文件模板')
    parser.add_argument('template', help='模板文件')
    parser.add_argument('replacement', help='字段映射')
    args = parser.parse_args()
    print(open(args.template).read().format(**json.loads(args.replacement)))

if __name__ == '__main__':
    main()
