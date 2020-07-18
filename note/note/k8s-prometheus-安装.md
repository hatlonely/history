---
title: k8s prometheus operator 安装
date: 2020-06-05 23:38:49
tags: [k8s, prometheus]
---

## 安装

```sh
helm install -n monitor prometheus-operator stable/prometheus-operator \
  --set grafana.ingress.enabled=true \
  --set grafana.ingress.hosts={k8s.grafana.hatlonely.com} \
  --set grafana.ingress.tls\[0\].secretName=k8s-dashboard-secret \
  --set grafana.ingress.tls\[0\].hosts={k8s.grafana.hatlonely.com}
```

## 检查

```sh
$ helm ls -n monitor

NAME                    NAMESPACE       REVISION        UPDATED                                 STATUS          CHART                           APP VERSION
prometheus-operator     monitor         1               2020-05-31 23:16:57.976284 +0800 CST    deployed        prometheus-operator-8.13.9      0.38.1     

$ kubectl get pods -n monitor

NAME                                                      READY   STATUS    RESTARTS   AGE
alertmanager-prometheus-operator-alertmanager-0           2/2     Running   0          5d
prometheus-operator-grafana-65f8668bf-p6hp5               2/2     Running   0          5d
prometheus-operator-kube-state-metrics-7f979567df-r9fts   1/1     Running   0          5d
prometheus-operator-operator-874c49dfb-mp7tl              2/2     Running   0          5d
prometheus-operator-prometheus-node-exporter-9n9n7        1/1     Running   0          5d
prometheus-operator-prometheus-node-exporter-gwd5w        1/1     Running   0          5d
prometheus-operator-prometheus-node-exporter-hrxxm        1/1     Running   0          5d
prometheus-operator-prometheus-node-exporter-rlfbl        1/1     Running   0          5d
prometheus-prometheus-operator-prometheus-0               3/3     Running   1          5d
```

## 删除

```sh
helm delete -n monitor prometheus-operator
```

## 访问

获取 ingress 绑定的 ip

```sh
$ kubectl get ingress -n monitor

NAME                          HOSTS                       ADDRESS        PORTS   AGE
prometheus-operator-grafana   k8s.grafana.hatlonely.com   192.168.0.13   80      5d
```

将 `192.168.0.13 k8s.grafana.hatlonely.com` 加入到 /etc/hosts 中，现在可以在浏览器中访问 grafana 了

通过如下方式获取用户名密码

```sh
kubectl get secrets -n monitor prometheus-operator-grafana -o json | jq -r '.data."admin-user"' | base64 --decode
kubectl get secrets -n monitor prometheus-operator-grafana -o json | jq -r '.data."admin-password"' | base64 --decode
```

## 链接

- github: <https://github.com/helm/charts/tree/master/stable/prometheus-operator>
