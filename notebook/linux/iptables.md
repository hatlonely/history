# iptables

## linux防火墙
iptables是linux防火墙
配置文件/etc/sysconfig/iptables，一般通过service iptable save修改

## samba服务器
# iptables -I INPUT -p udp --dport 137 -j ACCEPT &&
iptables -I INPUT -p udp --dport 138 -j ACCEPT &&
iptables -I INPUT -p tcp --dport 139 -j ACCEPT && 
iptables -I INPUT -p tcp --dport 445 -j ACCEPT
# service iptables save
# service iptables restart

## ftp服务器
ftp的主动模式和被动模式
# iptables -I INPUT -p tcp --dport 21 -j ACCEPT &&
iptables -I INPUT -p tcp --dport 20 -j ACCEPT &&
iptables -I INPUT -p tcp --dport 2222:2225 -j ACCEPT
# service iptables save
# service iptables restart
在/etc/vsftpd/vsftpd.conf中添加：
pasv_min_port=2222
pasv_max_port=2225
