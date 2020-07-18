package hashopt

import (
	"testing"

	"github.com/satori/go.uuid"
	. "github.com/smartystreets/goconvey/convey"
)

func TestStringHasherBKDR(t *testing.T) {
	BKDRHash := func(str string) uint64 {
		// var seed uint64 =  131// 31 131 1313 13131 131313 etc..
		var hash uint64
		for i := 0; i < len(str); i++ {
			hash = hash*131 + uint64(str[i])
		}
		return hash
	}

	Convey("djb hash 功能测试", t, func() {
		hasher := NewStringHasherBKDR()
		Println(hasher.AddStr("hello world"))
		Println(hasher.AddStr("hello").AddStr(" ").AddStr("world"))
		Println(hasher.AddInt(123456))
		So(uint64(hasher.AddStr("hello world")), ShouldEqual, BKDRHash("hello world"))
		So(hasher.AddStr("hello world").Val(), ShouldEqual, BKDRHash("hello world"))
		So(hasher.AddStr("hello").AddStr(" ").AddStr("world").Val(), ShouldEqual, BKDRHash("hello world"))
	})

	Convey("冲突测试", t, func() {
		m := map[uint64]struct{}{}
		hasher := NewStringHasherBKDR()
		for i := 0; i < 100000; i++ {
			m[hasher.AddStr(uuid.NewV4().String()).Val()] = struct{}{}
		}
		So(len(m), ShouldEqual, 100000)
	})
}
