#!/usr/bin/env python3
# pip install redis

import redis


def main():
    r = redis.Redis(host="localhost", port=6379, db=0)
    print(r.set("name", "hatlonely", ex=20))
    print(r.get("name"))
    print(r.setex("name", 20, "hatlonely"))


if __name__ == "__main__":
    main()
