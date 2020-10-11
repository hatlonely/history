工具-nginx
==========

安装和启动
--------

```
$ sudo yum install epel-release
$ sudo yum install nginx
$ sudo service nginx start
```

反向代理
-------

服务器N上部署nginx,服务器K上部署服务kibana,将N的请求完全转发到服务器K上

1. 编辑服务器N上的nginx配置, `sudo vi /etc/nginx/conf.d/kibana.conf`

```
server {
    server_name hatlonely.com;
    location / {
        proxy_pass http://123.123.123.123:5601/;
    }
}
```

2. 重启nginx, `service nginx restart`
