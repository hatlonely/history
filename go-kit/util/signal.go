package util

import (
	"os"
	"os/signal"
	"syscall"
)

// WaitStopSignal wait stop signal
func WaitStopSignal() {
	stop := make(chan os.Signal)
	signal.Notify(stop, syscall.SIGINT, syscall.SIGTERM)
	<-stop
}
