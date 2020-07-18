package hashopt

import (
	"testing"

	"github.com/satori/go.uuid"
	. "github.com/smartystreets/goconvey/convey"
)

func TestStringHasherDJB(t *testing.T) {
	DJBHash := func(str string) uint64 {
		hash := uint64(5381)
		for i := 0; i < len(str); i++ {
			hash = ((hash << 5) + hash) + uint64(str[i])
		}
		return hash
	}

	Convey("djb hash 功能测试", t, func() {
		hasher := NewStringHasherDJB()
		Println(hasher.AddStr("hello world"))
		Println(hasher.AddStr("hello").AddStr(" ").AddStr("world"))
		Println(hasher.AddInt(123456))
		Println(DJBHash("hello world"))
		So(uint64(hasher.AddStr("hello world")), ShouldEqual, DJBHash("hello world"))
		So(hasher.AddStr("hello world").Val(), ShouldEqual, DJBHash("hello world"))
		So(hasher.AddStr("hello").AddStr(" ").AddStr("world").Val(), ShouldEqual, DJBHash("hello world"))
	})

	Convey("冲突测试", t, func() {
		m := map[uint64]struct{}{}
		hasher := NewStringHasherDJB()
		for i := 0; i < 100000; i++ {
			m[hasher.AddStr(uuid.NewV4().String()).Val()] = struct{}{}
		}
		So(len(m), ShouldEqual, 100000)
	})
}
