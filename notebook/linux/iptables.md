# iptables

## linux����ǽ
iptables��linux����ǽ
�����ļ�/etc/sysconfig/iptables��һ��ͨ��service iptable save�޸�

## samba������
# iptables -I INPUT -p udp --dport 137 -j ACCEPT &&
iptables -I INPUT -p udp --dport 138 -j ACCEPT &&
iptables -I INPUT -p tcp --dport 139 -j ACCEPT && 
iptables -I INPUT -p tcp --dport 445 -j ACCEPT
# service iptables save
# service iptables restart

## ftp������
ftp������ģʽ�ͱ���ģʽ
# iptables -I INPUT -p tcp --dport 21 -j ACCEPT &&
iptables -I INPUT -p tcp --dport 20 -j ACCEPT &&
iptables -I INPUT -p tcp --dport 2222:2225 -j ACCEPT
# service iptables save
# service iptables restart
��/etc/vsftpd/vsftpd.conf����ӣ�
pasv_min_port=2222
pasv_max_port=2225
