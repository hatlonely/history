package cache

import (
	"testing"
	"time"

	"github.com/go-redis/redis"
	. "github.com/smartystreets/goconvey/convey"
)

func TestRedisCluster_Set_Get_Del(t *testing.T) {
	Convey("连接到本地 redis 集群", t, func() {
		redisCluster, err := NewRedisCluster(
			"127.0.0.1:7002",
			WithRetries(3),
			WithTimeout(time.Duration(240)*time.Millisecond),
			WithPoolSize(15),
		)
		So(err, ShouldBeNil)

		Convey("Get 一个不存在的值", func() {
			val, err := redisCluster.Get("name")
			So(err, ShouldEqual, redis.Nil)
			So(val, ShouldEqual, "")
		})

		Convey("Set 一个值", func() {
			err := redisCluster.Set("name", "hatlonely")
			So(err, ShouldBeNil)

			Convey("Get 这个值，可以 Get 到值", func() {
				val, err := redisCluster.Get("name")
				So(err, ShouldBeNil)
				So(val, ShouldEqual, "hatlonely")
			})

			Convey("Del 这个值", func() {
				err := redisCluster.Del("name")
				So(err, ShouldBeNil)

				Convey("再次 Get 这个值，已经不存在", func() {
					val, err := redisCluster.Get("name")
					So(err, ShouldEqual, redis.Nil)
					So(val, ShouldEqual, "")
				})
			})
		})
	})
}

func TestRedisCluster_SetExNx(t *testing.T) {
	Convey("连接到本地 redis 集群", t, func() {
		redisCluster, err := NewRedisCluster(
			"127.0.0.1:7002",
			WithRetries(3),
			WithTimeout(time.Duration(240)*time.Millisecond),
			WithPoolSize(15),
		)
		So(err, ShouldBeNil)

		Convey("SetExNx 一个值，这个值 Set 成功", func() {
			ok, err := redisCluster.SetExNx("name", "hatlonely", time.Duration(60)*time.Second)
			So(err, ShouldBeNil)
			So(ok, ShouldBeTrue)

			Convey("再次 SetExNx，这个值 Set 失败", func() {
				ok, err := redisCluster.SetExNx("name", "hatlonely", time.Duration(60)*time.Second)
				So(err, ShouldBeNil)
				So(ok, ShouldBeFalse)
			})
		})

		Convey("Del 这个值", func() {
			err := redisCluster.Del("name")
			So(err, ShouldBeNil)
		})
	})
}

func TestRedisCluster_SetExNxBatch(t *testing.T) {
	Convey("连接到本地 redis 集群", t, func() {
		redisCluster, err := NewRedisCluster(
			"127.0.0.1:7002",
			WithRetries(3),
			WithTimeout(time.Duration(240)*time.Millisecond),
			WithPoolSize(15),
		)
		So(err, ShouldBeNil)

		Convey("SetExNxBatch 一些值，这些值 Set 成功", func() {
			keys := []string{"key1", "key2", "key3"}
			vals := []interface{}{"val1", "val2", "val3"}
			oks, errs, err := redisCluster.SetExNxBatch(keys, vals, time.Duration(60)*time.Second)
			So(err, ShouldBeNil)
			So(oks, ShouldResemble, []bool{true, true, true})
			So(errs, ShouldResemble, []error{nil, nil, nil})

			Convey("再次 SetExNxBatch 这些值，这些值 Set 失败", func() {
				oks, errs, err := redisCluster.SetExNxBatch(keys, vals, time.Duration(60)*time.Second)
				So(err, ShouldBeNil)
				So(oks, ShouldResemble, []bool{false, false, false})
				So(errs, ShouldResemble, []error{nil, nil, nil})

				Convey("再次 SetExNxBatch 一些其他值，可以 Set 成功", func() {
					keys := []string{"key1", "key2", "key3", "key4"}
					vals := []interface{}{"val1", "val2", "val3", "val4"}
					oks, errs, err := redisCluster.SetExNxBatch(keys, vals, time.Duration(60)*time.Second)
					So(err, ShouldBeNil)
					So(oks, ShouldResemble, []bool{false, false, false, true})
					So(errs, ShouldResemble, []error{nil, nil, nil, nil})
				})
			})
		})

		Convey("Del 这些值", func() {
			for _, key := range []string{"key1", "key2", "key3", "key4"} {
				err := redisCluster.Del(key)
				So(err, ShouldBeNil)
			}
		})
	})
}

func TestRedisCluster_SetExsNxBatch(t *testing.T) {
	Convey("连接到本地 redis 集群", t, func() {
		redisCluster, err := NewRedisCluster(
			"127.0.0.1:7002",
			WithRetries(3),
			WithTimeout(time.Duration(240)*time.Millisecond),
			WithPoolSize(15),
		)
		So(err, ShouldBeNil)

		Convey("SetExNxBatch 一些值，这些值 Set 成功", func() {
			keys := []string{"key1", "key2", "key3"}
			vals := []interface{}{"val1", "val2", "val3"}
			exps := []time.Duration{time.Duration(60) * time.Second, time.Duration(60) * time.Second, time.Duration(60) * time.Second}
			oks, errs, err := redisCluster.SetExsNxBatch(keys, vals, exps)
			So(err, ShouldBeNil)
			So(oks, ShouldResemble, []bool{true, true, true})
			So(errs, ShouldResemble, []error{nil, nil, nil})

			Convey("再次 SetExNxBatch 这些值，这些值 Set 失败", func() {
				oks, errs, err := redisCluster.SetExsNxBatch(keys, vals, exps)
				So(err, ShouldBeNil)
				So(oks, ShouldResemble, []bool{false, false, false})
				So(errs, ShouldResemble, []error{nil, nil, nil})

				Convey("再次 SetExNxBatch 一些其他值，可以 Set 成功", func() {
					keys := []string{"key1", "key2", "key3", "key4"}
					vals := []interface{}{"val1", "val2", "val3", "val4"}
					exps := []time.Duration{time.Duration(60) * time.Second, time.Duration(60) * time.Second, time.Duration(60) * time.Second, time.Duration(60) * time.Second}
					oks, errs, err := redisCluster.SetExsNxBatch(keys, vals, exps)
					So(err, ShouldBeNil)
					So(oks, ShouldResemble, []bool{false, false, false, true})
					So(errs, ShouldResemble, []error{nil, nil, nil, nil})
				})
			})
		})

		Convey("Del 这些值", func() {
			for _, key := range []string{"key1", "key2", "key3", "key4"} {
				err := redisCluster.Del(key)
				So(err, ShouldBeNil)
			}
		})
	})
}

func TestRedisCluster_GetBatch(t *testing.T) {
	Convey("连接到本地 redis 集群", t, func() {
		redisCluster, err := NewRedisCluster(
			"127.0.0.1:7002",
			WithRetries(3),
			WithTimeout(time.Duration(240)*time.Millisecond),
			WithPoolSize(15),
		)
		So(err, ShouldBeNil)

		Convey("SetExNxBatch 一些值，这些值 Set 成功", func() {
			keys := []string{"key1", "key2", "key3"}
			vals := []interface{}{"val1", "val2", "val3"}
			oks, errs, err := redisCluster.SetExNxBatch(keys, vals, time.Duration(60)*time.Second)
			So(err, ShouldBeNil)
			So(oks, ShouldResemble, []bool{true, true, true})
			So(errs, ShouldResemble, []error{nil, nil, nil})

			Convey("GetBatch 这些值，可以成功 Get 这些值", func() {
				vals, errs, err := redisCluster.GetBatch(keys)
				So(err, ShouldBeNil)
				So(vals, ShouldResemble, []string{"val1", "val2", "val3"})
				So(errs, ShouldResemble, []error{nil, nil, nil})
			})
		})

		Convey("Del 这些值", func() {
			for _, key := range []string{"key1", "key2", "key3", "key4"} {
				err := redisCluster.Del(key)
				So(err, ShouldBeNil)
			}
		})
	})
}
