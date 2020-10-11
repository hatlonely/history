package main

import (
	"fmt"
	"github.com/go-redis/redis"
	"time"
)

func main() {
	client := redis.NewClient(&redis.Options{
		Addr:         "127.0.0.1:6379",
		DialTimeout:  20 * time.Millisecond,
		ReadTimeout:  20 * time.Millisecond,
		WriteTimeout: 20 * time.Millisecond,
		MaxRetries:   3,
		PoolSize:     20,
		DB:           0,
		//Password:     "123456",
	})

	if err := client.Set("name", "hatlonely", 20*time.Second).Err(); err != nil {
		panic(err)
	}

	if buf, err := client.Get("name").Result(); err != nil {
		if err == redis.Nil {
			fmt.Println("key not found")
		} else {
			panic(err)
		}
	} else {
		fmt.Println(string(buf))
	}
}
