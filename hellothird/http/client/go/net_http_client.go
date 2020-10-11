package main

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net"
	"net/http"
	"net/url"
	"time"
)

func main() {
	client := &http.Client{
		Transport: &http.Transport{
			DialContext: func(ctx context.Context, netw, addr string) (net.Conn, error) {
				c, err := net.DialTimeout(netw, addr, 100*time.Millisecond)
				if err != nil {
					return nil, err
				}
				return c, nil
			},
		},
		Timeout: 2000 * time.Microsecond,
	}

	buf, err := json.Marshal(map[string]string{
		"name": "hatlonely",
	})
	if err != nil {
		panic(err)
	}

	req, err := http.NewRequest("POST", "http://127.0.0.1:8000", bytes.NewBuffer(buf))
	if err != nil {
		panic(err)
	}
	query := &url.Values{}
	query.Add("name", "@Rajeev")
	query.Add("phone", "+861234567890")
	req.URL.RawQuery = query.Encode()
	req.Header.Add("User-Agent", `Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36`)

	resp, err := client.Do(req)
	if err != nil {
		panic(err)
	}

	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		panic(err)
	}
	fmt.Println(string(body))

	//result := &map[string]string{}
	//if err := json.NewDecoder(resp.Body).Decode(result); err != nil {
	//	panic(err)
	//}
	//fmt.Println(result)
}
