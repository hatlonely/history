# mac mini centos 8 安装

## 忘记密码重新登录系统

1. 启动按住 `command + s`，进入单用户模式
2. `/sbin/mount -uaw`
3. `rm /var/db/.applesetupdone`
4. `reboot`

重启后会重新进入系统，配置管理员用户

## 磁盘工具删除磁盘

1. 启动按住 `command + r` 选择磁盘工具
2. 抹掉磁盘
3. 重新分区，选 `free space`

## 制作 centos 安装盘

### `dracut-initqueue timeout` 解决办法

这个是因为系统无法找到我们的 u 盘，需要手动指定，等待超时之后输入命令：`ls /dev`，找到 `sdb[0-9]`，这个盘就是 u 盘所在位置，我的是 sdb4，记住这个盘，下面会用到

输入 `reboot` 重新启动，在页面选择 `install centos 8` 键入 `e` 修改

```
vmlinuz initrd=initrd.img inst.stage2=hd:LABEL=CentOS\x207\x20x86_64.check quiet
```

为

```
vmlinuz initrd=initrd.img inst.stage2=hd:/dev/sdb[0-9] quiet
```

按 `ctrl + x` 就好了

### `ctrl + x` ctrl 键失效

用 windows 打开 u 盘，找到文件 `/EFI/BOOT/grub.cfg`，直接修改上面语句即可

## centos 安装

centos 7 选自动分区，回收之前所有的空间，centos 8 引导程序装不上

- 软件选【带 GUI 的 Server】
- 网络选有线，有开关需要打开

