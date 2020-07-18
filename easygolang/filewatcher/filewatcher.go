package filewatcher

import (
	"path/filepath"
	"sync/atomic"
	"time"

	"github.com/fsnotify/fsnotify"
)

// onChangeHandlerState 枚举，因为这里需要用到atomic获取状态，所以使用原生类型int32
const (
	OnChangeStateFree  int32 = 0 // 空闲等待任务
	OnChangeStateDoing int32 = 1 // 正在处理任务
	OnChangeStateMore  int32 = 2 // 更多任务处理
)

// NewFileWatcher 创建一个新的 FileWatcher
func NewFileWatcher() (*FileWatcher, error) {
	watcher, err := fsnotify.NewWatcher()
	if err != nil {
		return nil, err
	}

	fn := &FileWatcher{
		onChangeHandlerMap: map[string]*OnChangeHandlerInfo{},
		watcher:            watcher,
	}

	return fn, nil
}

// OnChangeHandlerInfo 事件处理
type OnChangeHandlerInfo struct {
	onChangeHandlerPack  func(event fsnotify.Event, state *int32)
	onChangeHandlerState int32
}

// FileWatcher 文件监测器，当文件发生时变化，执行函数
type FileWatcher struct {
	watcher            *fsnotify.Watcher
	onChangeHandlerMap map[string]*OnChangeHandlerInfo
}

// Add 添加需要监测的文件，以及对应的处理
func (fn *FileWatcher) Add(dirbase string, onChangeHandler func(fsnotify.Event)) {
	// 这里可以添加重复的目录，内部用map实现
	fn.watcher.Add(filepath.Dir(dirbase))

	event := fsnotify.Event{Name: dirbase, Op: fsnotify.Create}
	onChangeHandler(event)

	fn.onChangeHandlerMap[filepath.Base(dirbase)] = &OnChangeHandlerInfo{
		onChangeHandlerState: OnChangeStateFree,
		onChangeHandlerPack: func(event fsnotify.Event, state *int32) {
			atomic.StoreInt32(state, OnChangeStateMore)
			// 只要有新的任务就一直处理
			for atomic.LoadInt32(state) == OnChangeStateMore {
				atomic.StoreInt32(state, OnChangeStateDoing)
				onChangeHandler(event)
			}
			// 任务处理完成
			atomic.StoreInt32(state, OnChangeStateFree)
		},
	}
}

// Watch 开始监测
func (fn *FileWatcher) Watch() {
	ticker := time.Tick(time.Duration(1800) * time.Second)
	for {
		select {
		case event := <-fn.watcher.Events:
			if event.Op&fsnotify.Write == fsnotify.Write || event.Op&fsnotify.Create == fsnotify.Create {
				if handlerInfo, ok := fn.onChangeHandlerMap[filepath.Base(event.Name)]; ok {
					switch atomic.LoadInt32(&handlerInfo.onChangeHandlerState) {
					case OnChangeStateFree: // 空闲处理任务
						handlerInfo.onChangeHandlerPack(event, &handlerInfo.onChangeHandlerState)
					case OnChangeStateDoing: // 任务处理中，新的任务标记为more
						atomic.StoreInt32(&handlerInfo.onChangeHandlerState, OnChangeStateMore)
					case OnChangeStateMore:
						// nothing to do
					default:
					}
				}
			}
		case err := <-fn.watcher.Errors:
			_ = err
		case <-ticker:
		}
	}
}
