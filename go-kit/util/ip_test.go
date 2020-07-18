package util

import "testing"

func TestLocalIp(t *testing.T) {
	if ip, err := LocalIP(); err != nil {
		t.Errorf("hlocal ip failed. ip: [%v], err: [%v].", ip, err)
	} else {
		t.Log(ip)
	}
}

func TestPublicIp(t *testing.T) {
	if ip, err := PublicIP(); err != nil {
		t.Errorf("hlocal ip failed. ip: [%v], err: [%v].", ip, err)
	} else {
		t.Log(ip)
	}
}
