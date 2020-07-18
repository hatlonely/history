package datastruct

import (
	"math/rand"
	"testing"

	. "github.com/smartystreets/goconvey/convey"
)

func TestSyncmapUint64String_All(t *testing.T) {
	Convey("创建一个新的 SyncmapUint64String", t, func() {
		sm := NewSyncmapUint64String(20)

		Convey("校验不存在的值", func() {
			_, ok := sm.Get(123)
			So(ok, ShouldBeFalse)
		})

		Convey("写入两个值", func() {
			sm.Set(123, "hello")
			sm.Set(456, "world")

			Convey("校验值写入成功", func() {
				val, ok := sm.Get(123)
				So(val, ShouldEqual, "hello")
				So(ok, ShouldBeTrue)
				val, ok = sm.Get(456)
				So(val, ShouldEqual, "world")
				So(ok, ShouldBeTrue)
			})
		})

		Convey("删除这两个值", func() {
			sm.Del(123)
			sm.Del(456)

			Convey("校验值写入成功", func() {
				_, ok := sm.Get(123)
				So(ok, ShouldBeFalse)
				_, ok = sm.Get(456)
				So(ok, ShouldBeFalse)
			})
		})
	})
}

func BenchmarkSyncmapUint64String_All(b *testing.B) {
	sm := NewSyncmapUint64String(20)
	b.RunParallel(func(pb *testing.PB) {
		for pb.Next() {
			for i := 0; i < 1000; i++ {
				sm.Set(rand.Uint64(), "hello world")
			}
		}
	})
	b.RunParallel(func(pb *testing.PB) {
		for pb.Next() {
			for i := 0; i < 1000; i++ {
				sm.Get(rand.Uint64())
			}
		}
	})
	b.RunParallel(func(pb *testing.PB) {
		for pb.Next() {
			for i := 0; i < 1000; i++ {
				sm.Del(rand.Uint64())
			}
		}
	})
}
