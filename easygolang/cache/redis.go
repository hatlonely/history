package cache

import (
	"strings"
	"time"

	"github.com/go-redis/redis"
)

// NewRedisCluster 创建一个新的 redis cluster 客户端
func NewRedisCluster(address string, opts ...ClusterOption) (*RedisCluster, error) {
	redisCluster := &RedisCluster{}
	options := defaultClusterOptions
	for _, o := range opts {
		o(&options)
	}
	options.Addrs = strings.Split(address, ",")

	redisCluster.client = redis.NewClusterClient(&options)
	if err := redisCluster.client.Ping().Err(); err != nil {
		return nil, err
	}

	return redisCluster, nil
}

var defaultClusterOptions = redis.ClusterOptions{
	Addrs:        []string{"127.0.0.1:7000"},
	DialTimeout:  time.Duration(1000) * time.Millisecond,
	ReadTimeout:  time.Duration(1000) * time.Millisecond,
	WriteTimeout: time.Duration(1000) * time.Millisecond,
	MaxRetries:   3,
	PoolSize:     20,
}

// ClusterOption 选项
type ClusterOption func(*redis.ClusterOptions)

// WithRetries 设置重试次数
func WithRetries(retries int) ClusterOption {
	return func(options *redis.ClusterOptions) {
		options.MaxRetries = retries
	}
}

// WithTimeout 设置超时时间
func WithTimeout(timeout time.Duration) ClusterOption {
	return func(options *redis.ClusterOptions) {
		options.DialTimeout = timeout
		options.ReadTimeout = timeout
		options.WriteTimeout = timeout
	}
}

// WithPoolSize 设置连接池大小
func WithPoolSize(poolsize int) ClusterOption {
	return func(options *redis.ClusterOptions) {
		options.PoolSize = poolsize
	}
}

// RedisCluster redis 集群客户端封装
type RedisCluster struct {
	client *redis.ClusterClient
}

// Get 获取值
func (rc *RedisCluster) Get(key string) (string, error) {
	return rc.client.Get(key).Result()
}

// Set 设置值
func (rc *RedisCluster) Set(key string, val interface{}) error {
	return rc.client.Set(key, val, time.Duration(0)).Err()
}

// Del 删除值
func (rc *RedisCluster) Del(key string) error {
	return rc.client.Del(key).Err()
}

// SetExNx 如果值不存在则设置值和过期时间
func (rc *RedisCluster) SetExNx(key string, val interface{}, exp time.Duration) (bool, error) {
	return rc.client.SetNX(key, val, exp).Result()
}

// SetExNxBatch 批量设置值和过期时间，过期时间相同
func (rc *RedisCluster) SetExNxBatch(keys []string, vals []interface{}, exp time.Duration) ([]bool, []error, error) {
	pipe := rc.client.Pipeline()
	defer pipe.Close()
	cmds := make([]*redis.BoolCmd, len(keys))

	for i := range keys {
		cmds[i] = pipe.SetNX(keys[i], vals[i], exp)
	}

	if _, err := pipe.Exec(); err != nil {
		return nil, nil, err
	}

	oks := make([]bool, len(keys))
	errs := make([]error, len(keys))
	for i, cmd := range cmds {
		oks[i] = cmd.Val()
		errs[i] = cmd.Err()
	}

	return oks, errs, nil
}

// SetExsNxBatch 批量设置值和过期时间，key 与过期时间一一对应
func (rc *RedisCluster) SetExsNxBatch(keys []string, vals []interface{}, exp []time.Duration) ([]bool, []error, error) {
	pipe := rc.client.Pipeline()
	defer pipe.Close()
	cmds := make([]*redis.BoolCmd, len(keys))

	for i := range keys {
		cmds[i] = pipe.SetNX(keys[i], vals[i], exp[i])
	}

	if _, err := pipe.Exec(); err != nil {
		return nil, nil, err
	}

	oks := make([]bool, len(keys))
	errs := make([]error, len(keys))
	for i, cmd := range cmds {
		oks[i] = cmd.Val()
		errs[i] = cmd.Err()
	}

	return oks, errs, nil
}

// GetBatch 批量获取值
func (rc *RedisCluster) GetBatch(keys []string) ([]string, []error, error) {
	pipe := rc.client.Pipeline()
	defer pipe.Close()
	cmds := make([]*redis.StringCmd, len(keys))
	for i, key := range keys {
		cmds[i] = pipe.Get(key)
	}

	if _, err := pipe.Exec(); err != nil {
		return nil, nil, err
	}

	vals := make([]string, len(keys))
	errs := make([]error, len(keys))
	for i, cmd := range cmds {
		errs[i] = cmd.Err()
		vals[i] = cmd.Val()
	}

	return vals, errs, nil
}
