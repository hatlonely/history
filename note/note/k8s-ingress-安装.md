---
title: k8s ingress 安装
date: 2020-06-05 23:38:49
tags: [k8s, ingress]
---

## 安装

```sh
helm install -n kube-system nginx-ingress stable/nginx-ingress \
  --set controller.metrics.enabled=true \
  --set rbac.create=true \
  --set defaultBackend.image.repository=docker.io/mirrorgooglecontainers/defaultbackend-amd64 \
  --set controller.hostNetwork=true
```

`controller.hostNetwork=true` 表示使用本地机器的网络，ingress 将通过本地机器的端口直接对外

## 删除

```sh
helm delete -n kube-system nginx-ingress
```

## 检查

```
$ helm ls -n kube-system

NAME            NAMESPACE       REVISION        UPDATED                                 STATUS          CHART                   APP VERSION
nginx-ingress   kube-system     2               2020-05-31 12:30:25.823701 +0800 CST    deployed        nginx-ingress-1.39.0    0.32.0  

$ kubectl get pods -n kube-system

NAME                                            READY   STATUS    RESTARTS   AGE
nginx-ingress-controller-565f79fbd6-lvznl       1/1     Running   0          5d11h
nginx-ingress-default-backend-7b9bffcbf-ds89c   1/1     Running   0          5d11h
```

## 链接

- github: <https://github.com/helm/charts/tree/master/stable/nginx-ingress>
