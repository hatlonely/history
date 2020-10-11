package hclould

import "testing"

var hrouter *HRouter

func TestHRouter_Init(t *testing.T) {
	hrouter = &HRouter{}
	hrouter.Init("../../conf/hclould.json")
}
