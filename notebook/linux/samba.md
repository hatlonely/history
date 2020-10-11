# samba.md

## 安装
sudo yum install samba

## 启动
开机启动
sudo chkconfig smb on
启动
service smb start
重新启动
service smb restart

## 添加samba用户
sudo smbpasswd -a <user_name>

## 不能访问的原因
1. 防火墙
关闭防火墙
service iptables stop
开启防火墙
service iptables start
2. selinux
暂停selinux
setenforce 0
启动selinux
setenforce 1
