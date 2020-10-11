package main

import (
	"fmt"
	"github.com/hatlonely/hgo/src/hutil"
	"gopkg.in/alecthomas/kingpin.v2"
	"hservices"
	"net/http"
	_ "net/http/pprof"
)

func main() {
	kingpin.Parse()

	go http.ListenAndServe(fmt.Sprintf("localhost:%v", *PprofPort), nil)

	if err := hservices.Init("conf/hservices.conf"); err != nil {
		panic(err)
	}

	go hservices.Run()

	hutil.WaitSignalToStop()
}
