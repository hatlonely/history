# redis 服务测试命令

# 查看帮助
redis-server -h

# 使用默认配置启动服务
redis-server

# 使用配置文件启动服务
redis-server /etc/redis/6379.conf

# 指定服务端口启动服务
redis-server --port 7777

# 多个服务组成集群
redis-trib.rb create --replicas 1 127.0.0.1:7000 127.0.0.1:7001 127.0.0.1:7002 <<EOF
yes
EOF
