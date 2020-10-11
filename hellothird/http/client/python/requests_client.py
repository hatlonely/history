#!/usr/bin/env python3

import requests


def main():
    res = requests.post("http://127.0.0.1:8000", params={
        "name": "@Rajeev",
        "phone": "+861234567890"
    }, json={
        "name": "hatlonely"
    }, headers={
        "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36"
    })
    print(res.text)


if __name__ == "__main__":
    main()
