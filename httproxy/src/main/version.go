package main

import (
	"gopkg.in/alecthomas/kingpin.v2"
)

var Version = "unknown"
var PprofPort *string

func init() {
	kingpin.HelpFlag.Short('h')
	PprofPort = kingpin.Flag("pprof", "性能监控端口").Default("6060").Short('p').String()
	kingpin.Version(Version)
}
