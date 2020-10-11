# mongo 客户端

# 链接 mongodb
mongo 127.0.0.1:27017/mydatabase

# mongo client 操作

# 使用 db，如果 db 不存在，有数据插入时创建
use mydb

# 插入数据，第一次插入数据时，自动创建 collection
db.mycollection.insert({name: "hatlonely", weight: 80})

# 删除一条
db.mycollection.deleteOne({name: "hatlonely"})

# 删除所有
db.mycollection.deleteMany({name: "hatlonely"})

# 更新一条
db.mycollection.updateOne({name: "hatlonely"}, {"$set": {weight: 70}})

# 更新所有
db.mycollection.updateMany({name: "hatlonely"}, {"$set": {weight: 70}})

# 查找所有
db.mycollection.find({})

# 条件查找
db.mycollection.find({weight: {"$exists": true, "$lt": 100, "$gt": 75}, name: "hatlonely"})

# 字段选择
db.mycollection.find({}, {name: 1})

# 排序
db.mycollection.find({}).sort({weight: 1})
