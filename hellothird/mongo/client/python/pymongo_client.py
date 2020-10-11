#!/usr/bin/env python3
# pip3 install pymongo

import pymongo


def main():
    client = pymongo.MongoClient("localhost", 27017)
    db = client.mydb
    db.mycollection.insert_one({"name": "hatlonely", "value": 20})
    res = db.mycollection.find_one({})
    print(res)


if __name__ == "__main__":
    main()
