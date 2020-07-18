package filewatcher

import (
	"fmt"
	"os"
	"testing"
	"time"

	"github.com/fsnotify/fsnotify"
)

func TestFileWatcher_Watch(t *testing.T) {
	fn, _ := NewFileWatcher()
	fn.Add("/tmp/foo", func(event fsnotify.Event) {
		fmt.Printf("handler file [%s]\n", event.Name)
	})
	fn.Add("/tmp/bar", func(event fsnotify.Event) {
		fmt.Printf("handler file [%s]\n", event.Name)
	})
	go fn.Watch()
	{
		foo, _ := os.Create("/tmp/foo")
		foo.WriteString("hello foo")
		foo.Close()
	}
	time.Sleep(time.Duration(200) * time.Millisecond)
	{
		bar, _ := os.Create("/tmp/bar")
		bar.WriteString("hello bar")
		bar.Close()
	}
	time.Sleep(time.Duration(200) * time.Millisecond)
}
