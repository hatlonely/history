package hashopt

import (
	"testing"

	"github.com/satori/go.uuid"
	. "github.com/smartystreets/goconvey/convey"
)

func TestStringHasherBKDRFixed(t *testing.T) {
	Convey("djb hash 功能测试", t, func() {
		hasher := NewStringHasherBKDRFixed()
		Println(hasher.Hash("hello world"))
	})

	Convey("冲突测试", t, func() {
		m := map[uint64]struct{}{}
		hasher := NewStringHasherBKDRFixed()
		for i := 0; i < 100000; i++ {
			m[hasher.Hash(uuid.NewV4().String()).Val()] = struct{}{}
		}
		So(len(m), ShouldEqual, 100000)
	})
}
