#!/usr/bin/python

import requests
import json
import argparse
from pyzabbix import ZabbixAPI


def zone_ips_from_consul(service="", consul="localhost:8500"):
    if not service:
        url = "http://{}/v1/catalog/services".format(consul)
    else:
        url = "http://{}/v1/health/service/{}?passing=true".format(
            consul, service)
    res = requests.get(url)
    if res.status_code != 200:
        print(res.status_code, res.reason)
        print(url)
        return None
    nodes = json.loads(res.text)
    zone_ips_map = {}
    for node in nodes:
        zone = str(node["Service"]["Meta"]["zone"])
        if zone not in zone_ips_map:
            zone_ips_map[zone] = []
        ip = str(node["Service"]["Meta"]["publicIP"])
        if ip not in zone_ips_map[zone]:
            zone_ips_map[zone].append(ip)
    return zone_ips_map


def kvput_to_consul(obj, dst, consul="localhost:8500"):
    url = "http://{}/v1/kv/{}".format(consul, dst)
    text = json.dumps(obj)
    res = requests.put(url, text)
    if res.status_code != 200:
        print(res.status_code, res.reason)
        print(url)
    else:
        print(text)


def avg_cpu_from_zabbix(ips, tag, zabbixUrl, user, password):
    zapi = ZabbixAPI(zabbixUrl)
    zapi.login(user, password)
    hostgroup = zapi.hostgroup.get(filter={"name": tag})
    groupid = hostgroup[0]["groupid"]
    hosts = zapi.host.get(groupids=groupid)
    hostids = []
    for host in hosts:
        if host["host"].split('_')[-1] in ips:
            hostids.append(str(host["hostid"]))
    items = zapi.item.get(
        hostids=hostids,
        search={"key_": "system.cpu.load[percpu,avg1]"},
    )
    sum_cpu = 0
    count = 0
    for item in items:
        count += 1
        sum_cpu += float(item['lastvalue']) * 100
    return int(sum_cpu / count)


def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description="""Example:
    python zone_cpu.py --service rs --tag adserver_ranker --zabbix zabbixUrl --user user --password password --consul localhost:8500
    python zone_cpu.py --service rs --tag adserver_ranker --zabbix http://mobmonitor.mobvista.com --user can.shen --password Mobvista_123 --consul localhost:8500
""",
    )
    parser.add_argument("-c", "--consul", default="localhost:8500",
                        help="consul address")
    parser.add_argument("-s", "--service", required=True,
                        help="consul service name")
    parser.add_argument("-t", "--tag", required=True,
                        help="zabbix tag name")
    parser.add_argument("-z", "--zabbix", required=True, help="zabbix url")
    parser.add_argument("-u", "--user", required=True, help="user name")
    parser.add_argument("-p", "--password", required=True, help="password")
    args = parser.parse_args()

    zone_ips_map = zone_ips_from_consul(args.service, args.consul)
    zone_avg_cpu = {}
    for zone in zone_ips_map:
        ips = zone_ips_map[zone]
        avg_cpu = avg_cpu_from_zabbix(
            ips, args.tag, args.zabbix, args.user, args.password,
        )
        zone_avg_cpu[zone] = avg_cpu
    kvput_to_consul(
        zone_avg_cpu, "{}/zone_cpu.json".format(args.service), args.consul,
    )


if __name__ == '__main__':
    main()
