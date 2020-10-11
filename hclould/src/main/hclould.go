package main

import (
	"gopkg.in/alecthomas/kingpin.v2"
	"hclould"
)

func main() {
	kingpin.Parse()

	clould := &hclould.HRouter{}
	clould.Init("conf/hclould.json")
	clould.Run()
}
