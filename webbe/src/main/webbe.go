package main

import (
	"fmt"
	"gopkg.in/alecthomas/kingpin.v2"
	"net/http"
	_ "net/http/pprof"
	"webbe"
	"github.com/hatlonely/hgo/src/hutil"
)

func main() {
	kingpin.Parse()

	go http.ListenAndServe(fmt.Sprintf("localhost:%v", *PprofPort), nil)

	if err := webbe.Init("conf/webbe.json"); err != nil {
		panic(err)
	}

	go webbe.Run()

	hutil.WaitSignalToStop()
}
