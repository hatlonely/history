---
title: k8s dashboard 安装
date: 2020-06-04 23:38:49
tags: [k8s, dashboard]
---

## 安装

```sh
kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/v2.0.1/aio/deploy/recommended.yaml
```

## 删除

```sh
kubectl delete -f https://raw.githubusercontent.com/kubernetes/dashboard/v2.0.1/aio/deploy/recommended.yaml
```

## 检查

```sh
$ kubectl get pods -n kubernetes-dashboard

dashboard-metrics-scraper-c79c65bb7-jcqsh   1/1     Running   0          4d4h
kubernetes-dashboard-6f89967466-x5vlx       1/1     Running   0          4d4h
```

## 访问

`kubectl proxy` 在本地启动 dashboard 服务

```sh
kubectl proxy
```

在浏览器中输入进入登录界面 <http://localhost:8001/api/v1/namespaces/kubernetes-dashboard/services/https:kubernetes-dashboard:/proxy/.>


## 获取 token

第一次需要新建登录账号

```sh
kubectl create sa dashboard-admin -n kube-system
kubectl create clusterrolebinding dashboard-admin --clusterrole=cluster-admin --serviceaccount=kube-system:dashboard-admin
```

获取登录 token

```sh
ADMIN_SECRET=$(kubectl get secrets -n kube-system | grep dashboard-admin | awk '{print $1}')
DASHBOARD_LOGIN_TOKEN=$(kubectl describe secret -n kube-system ${ADMIN_SECRET} | grep -E '^token' | awk '{print $2}')
echo ${DASHBOARD_LOGIN_TOKEN}
```

## 链接

- 官网: <https://kubernetes.io/docs/tasks/access-application-cluster/web-ui-dashboard/>
- github: <https://github.com/kubernetes/dashboard/>
