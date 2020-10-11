# redis-cli 客户端测试命令

# 查看帮助
redis-cli -h

# 指定主机和端口，密码和 db
redis-cli -h 127.0.0.1:7001 -a 123456 -n 10

# 执行单条命令
redis-cli set name hatlonely
redis-cli get name

# 查看 redis 信息
redis-cli info
