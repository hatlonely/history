package hashopt

import (
	"hash/fnv"
	"testing"

	"github.com/spaolacci/murmur3"
)

func BenchmarkMurmur3(b *testing.B) {
	for i := 0; i < b.N; i++ {
		for j := 0; j < 100; j++ {
			murmur3.Sum64([]byte("0a9599d1-0920-4e97-b8fe-8407ccf0f387"))
		}
	}
}

func BenchmarkHash(b *testing.B) {
	for i := 0; i < b.N; i++ {
		for j := 0; j < 100; j++ {
			h := fnv.New64a()
			h.Write([]byte("0a9599d1-0920-4e97-b8fe-8407ccf0f387"))
			h.Sum64()
		}
	}
}

func BenchmarkStringHasherDJB(b *testing.B) {
	hasher := NewStringHasherDJB()
	for i := 0; i < b.N; i++ {
		for j := 0; j < 100; j++ {
			hasher.AddStr("0a9599d1-0920-4e97-b8fe-8407ccf0f387").Val()
		}
	}
}

func BenchmarkStringHasherBKDR(b *testing.B) {
	hasher := NewStringHasherBKDR()
	for i := 0; i < b.N; i++ {
		for j := 0; j < 100; j++ {
			hasher.AddStr("0a9599d1-0920-4e97-b8fe-8407ccf0f387").Val()
		}
	}
}

func BenchmarkStringHasherBKDRFixed(b *testing.B) {
	hasher := NewStringHasherBKDRFixed()
	for i := 0; i < b.N; i++ {
		for j := 0; j < 100; j++ {
			hasher.Hash("0a9599d1-0920-4e97-b8fe-8407ccf0f387").Val()
		}
	}
}

func BenchmarkStringHasherDJBWithMultiStrings(b *testing.B) {
	hasher := NewStringHasherDJB()
	for i := 0; i < b.N; i++ {
		hasher.AddStr("hello").AddStr(" ").AddStr("world").Val()
	}
}

func BenchmarkStringHasherBKDRWithMultiStrings(b *testing.B) {
	hasher := NewStringHasherBKDR()
	for i := 0; i < b.N; i++ {
		hasher.AddStr("hello").AddStr(" ").AddStr("world").Val()
	}
}
