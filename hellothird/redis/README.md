# Redis

## 安装

- Mac: `brew install redis`
- Linux: `yum install redis`

集群模式下需要使用 redis-trib.rb 脚本，这个脚本默认不在安装包中，需要从源码 `src/redis-trib.rb` 中拷贝

源码安装:

```
function install_redis() {
    mkdir -p source && cd source &&
    wget http://download.redis.io/releases/redis-4.0.9.tar.gz &&
    tar -xzvf redis-4.0.9.tar.gz &&
    cd redis-4.0.9 &&
    make -j8 &&
    PREFIX=$1 make install &&
    cp src/redis-trib.rb $1/bin
}

install_redis $HOME/local
```

## 启动

### 普通模式

redis-server [/path/to/redis.conf]

### 集群模式

``` sh
redis-server [path/to/7000/redis.conf]
redis-server [path/to/7001/redis.conf]
redis-server [path/to/7002/redis.conf]

redis-trib.rb create --replicas 1 127.0.0.1:7000 127.0.0.1:7001 127.0.0.1:7002 <<EOF
yes
EOF
```

## 常见问题

## 链接

- redis 官网: <https://redis.io/>
- redis 中文网: <https://www.redis.net.cn/>
