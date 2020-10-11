# selinux

## 开关
setenforce 0 // 关闭
setenforce 1 // 开启

## samba
getsebool -a | grep samba
放行samba
setsebool -P samba_enable_home_dirs=1
samba配置文件/etc/samba/smb.conf取消以下两行注释
setsebool -P samba_domain_controller on
setsebool -P samba_enable_home_dirs on
