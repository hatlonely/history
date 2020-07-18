---
title: k8s jenkins 安装
date: 2020-06-05 23:38:49
tags: [k8s, ingress]
---

## 安装

```sh
helm repo add jenkins https://raw.githubusercontent.com/jenkinsci/kubernetes-operator/master/chart

helm install -n jenkins jenkins stable/jenkins \
    --set persistence.existingClaim=jenkins-pvc
```

## 链接

- jenkins 官网: https://jenkinsci.github.io/kubernetes-operator/docs/installation/
- github: https://github.com/jenkinsci/kubernetes-operator


```sh

cat <<EOF | kubectl apply -f -
apiVersion: storage.k8s.io/v1
kind: StorageClass
metadata:
  name: local
provisioner: kubernetes.io/no-provisioner
volumeBindingMode: WaitForFirstConsumer
EOF

cat <<EOF | kubectl apply -f -
kind: PersistentVolumeClaim
apiVersion: v1
metadata:
  namespace: jenkins
  name: jenkins-pvc
spec:
  storageClassName: local
  accessModes:
    - ReadWriteOnce
  resources:
    requests:
      storage: 32Gi
EOF


helm install -n jenkins jenkins stable/jenkins \
    --set persistence.existingClaim=jenkins-pvc


kind: PersistentVolume
apiVersion: v1
metadata:
  name: postgres-data
  labels:
    type: local
spec:
  storageClassName: local-storage
  capacity:
    storage: 1Gi
  local:
    path: /data/postgres
  persistentVolumeReclaimPolicy: Retain
  accessModes:
    - ReadWriteOnce
  storageClassName: local-storage
  nodeAffinity:
    required:
      nodeSelectorTerms:
        - matchExpressions:
          - key: app
            operator: In
            values:
              - postgres

```