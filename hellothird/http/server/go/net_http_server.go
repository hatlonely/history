package main

import (
	"encoding/json"
	"fmt"
	"net/http"
)

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		body := map[string]string{}
		if err := json.NewDecoder(r.Body).Decode(&body); err != nil {
			fmt.Println(err)
		}
		fmt.Println("header:", r.Header)
		fmt.Println("query:", r.URL.Query())
		fmt.Println("body:", body)
		w.WriteHeader(http.StatusOK)
		w.Write([]byte("hello " + body["name"]))
	})

	//fs := http.FileServer(http.Dir("static/"))
	//http.Handle("/static/", http.StripPrefix("/static/", fs))

	if err := http.ListenAndServe(":8000", nil); err != nil {
		panic(err)
	}
}
