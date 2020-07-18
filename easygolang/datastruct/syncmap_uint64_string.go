package datastruct

import (
	"sync"
)

// NewSyncmapUint64String 返回一个新的线程安全的 uint64 -> string map
// 为了减少锁的粒度，增大并发，内部采用多个 map 实现，参数 num 用来指定内部 map 的个数
func NewSyncmapUint64String(num int) *SyncmapUint64String {
	sm := &SyncmapUint64String{}
	sm.kvs = make([]map[uint64]string, num)
	for i := range sm.kvs {
		sm.kvs[i] = map[uint64]string{}
	}
	sm.mutexs = make([]sync.RWMutex, num)
	return sm
}

// SyncmapUint64String 线程安全 uint64 -> string map
type SyncmapUint64String struct {
	kvs    []map[uint64]string
	mutexs []sync.RWMutex
}

// Get 获取值
func (sm *SyncmapUint64String) Get(key uint64) (string, bool) {
	idx := key % uint64(len(sm.mutexs))
	sm.mutexs[idx].RLock()
	val, ok := sm.kvs[idx][key]
	sm.mutexs[idx].RUnlock()
	return val, ok
}

// Set 设置值
func (sm *SyncmapUint64String) Set(key uint64, val string) {
	idx := key % uint64(len(sm.mutexs))
	sm.mutexs[idx].Lock()
	sm.kvs[idx][key] = val
	sm.mutexs[idx].Unlock()
}

// Del 删除值
func (sm *SyncmapUint64String) Del(key uint64) {
	idx := key % uint64(len(sm.mutexs))
	sm.mutexs[idx].Lock()
	delete(sm.kvs[idx], key)
	sm.mutexs[idx].Unlock()
}
