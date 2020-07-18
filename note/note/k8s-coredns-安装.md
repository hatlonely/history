---
title: k8s coredns 安装
date: 2020-06-05 23:38:49
tags: [k8s, coredns]
---

## 安装

```sh
export CLUSTER_DNS_SVC_IP="10.254.0.2"
export CLUSTER_DNS_DOMAIN="cluster.local"
git clone https://github.com/coredns/deployment.git
cd deployment
./deploy.sh -i ${CLUSTER_DNS_SVC_IP} -d ${CLUSTER_DNS_DOMAIN} | kubectl apply -f -
```

kube-system 空间下会出现 coredns 的 pods

```sh
kubectl get pods -n kube-system

coredns-59c6ddbf5d-tn862                        1/1     Running   0          7d20h
```

## 链接

- github: <https://github.com/coredns/deployment>

