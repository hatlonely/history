package main

import (
	"fmt"
	"github.com/hatlonely/hgo/src/hutil"
	"gopkg.in/alecthomas/kingpin.v2"
	"httproxy"
	"net/http"
	_ "net/http/pprof"
)

func main() {
	kingpin.Parse()

	go http.ListenAndServe(fmt.Sprintf("localhost:%v", *PprofPort), nil)

	if err := httproxy.Init("conf/httproxy.json"); err != nil {
		panic(err)
	}

	go httproxy.Run()

	hutil.WaitSignalToStop()
}
