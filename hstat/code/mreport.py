#!/usr/bin/env python3

import elasticsearch
import argparse
import sys
import json
import datetime
import subprocess


class EsClient(object):
    def __init__(self, host=None, user=None, password=None):
        if host is None:
            host = 'localhost:9200'
        if user is None:
            user = 'elastic'
        if password is None:
            password = 'changeme'
        self.esclient = elasticsearch.Elasticsearch([host], http_auth=(user, password))
        self.host = host
        self.user = user
        self.password = password

    def put(self, index, doctype, docid, body):
        print('PUT {}/{}/{}/{} -d {} -u {}:{}'.format(self.host, index, doctype, docid, body, self.user, self.password))
        self.esclient.index(index=index, doc_type=doctype, id=docid, body=body)

    def clean(self, index, doctype, day):
        body = {'query': {'range': {
            '@timestamp': {'lt': 'now-{}d'.format(day)}
        }}}
        print('DEL {}/{}/{} -d {} -u {}:{}'.format(self.host, index, doctype, body, self.user, self.password))
        self.esclient.delete_by_query(index=index, doc_type=doctype, body=body)

    def delete(self, index, doctype, body):
        print('DEL {}/{}/{} -d {} -u {}:{}'.format(self.host, index, doctype, body, self.user, self.password))
        self.esclient.delete_by_query(index=index, doc_type=doctype, body=body)

    def get(self, index, doctype, body):
        print('GET {}/{}/{}/_search -d {} -u {}:{}'.format(self.host, index, doctype, body, self.user, self.password))
        print(self.esclient.search(index=index, doc_type=doctype, body=body))


class Util(object):
    @staticmethod
    def public_ip():
        cmd = 'GET http://169.254.169.254/latest/meta-data/public-ipv4'
        status, output = subprocess.getstatusoutput(cmd)
        if status != 0:
            return 'unknown'
        return output


class LogParser(object):
    @staticmethod
    def parse_satlog(line, ip):
        time_body = line.split('\t')
        timenow = datetime.datetime.strptime(time_body[0], '%Y-%m-%d %H:%M:%S')
        body = json.loads(time_body[1])
        body['@timestamp'] = timenow - datetime.timedelta(hours=8)
        body['@ip'] = ip
        docid = '{}_{}'.format(timenow.strftime('%Y%m%d%H%M'), ip)
        return docid, body

    @staticmethod
    def parse_python(line):
        return eval(line)


def main():
    parser = argparse.ArgumentParser(description='数据监控')
    parser.add_argument('-s', '--host', help='elasticsearch地址')
    parser.add_argument('-u', '--user', help='用户名')
    parser.add_argument('-p', '--password', help='密码')
    parser.add_argument('-m', '--method', help='方法', choices=['get', 'put', 'clean', 'del'], default='put')
    parser.add_argument('-i', '--index', help='index')
    parser.add_argument('-t', '--doctype', help='doctype')
    parser.add_argument('-l', '--logtype', help='logtype')
    args = parser.parse_args()

    if args.method == 'put':
        ip = Util.public_ip()
        client = EsClient(args.host, args.user, args.password)
        if args.logtype == 'satlog':
            for line in sys.stdin:
                docid, body = LogParser.parse_satlog(line, ip)
                client.put(args.index, args.doctype, docid, body)
        if args.logtype == 'python':
            for line in sys.stdin:
                index, doctype, docid, body = LogParser.parse_python(line)
                client.put(index, doctype, docid, body)


if __name__ == '__main__':
    main()
