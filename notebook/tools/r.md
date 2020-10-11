# R语言

## 向量
matrix(c, ncol=cols) 把结果转化成cols列的矩阵
sapply(c, func) 对vector中的每个元素执行func函数
cumsum(c) 计算累加的值
mean(c) 计算算术平均
mean(c, na.rm = T) 移除NA元素的算术平均
NA缺失的值，NULL不存在的值
subset(c, condition) 获取子集，去掉NA值
c[condition] 获取子集，包含NA值
which(condition] 获取满足条件的下标
ifelse(condition, a, b) condition ? a : b
diff(c) 计算后一个值与前一个值得差
sign(c) 返回各个元素的符号
all(x == y) 测试两个向量是否完全一样
```
> func <- function(x) return c(x, x^2, x^3)
> func(1:8)
[1]   1   2   3   4   5   6   7   8   1   4   9  16  25  36  49  64   1   8  27
[20]  64 125 216 343 512
> matrix(func(1:8), ncol=3)
[,1] [,2] [,3]
[1,]    1    1    1
[2,]    2    4    8
[3,]    3    9   27
[4,]    4   16   64
[5,]    5   25  125
[6,]    6   36  216
[7,]    7   49  343
[8,]    8   64  512
> sapply(1:8, func)
[,1] [,2] [,3] [,4] [,5] [,6] [,7] [,8]
[1,]    1    2    3    4    5    6    7    8
[2,]    1    4    9   16   25   36   49   64
[3,]    1    8   27   64  125  216  343  512
> mean(c(1:8, NA))
[1] NA
> mean(c(1:8, NA), na.rm = T)
[1] 4.5
> mean(c(1:8, NULL))
[1] 4.5
> x
[1]  1  2  3  4  5  6  7  8 NA
> x > 4
[1] FALSE FALSE FALSE FALSE  TRUE  TRUE  TRUE  TRUE    NA
> x[x > 4]
[1]  5  6  7  8 NA
> subset(x, x > 4)
[1] 5 6 7 8
> which(x > 4)
[1] 5 6 7 8
```

## 矩阵
矩阵是按列存储的向量
rbind 按行组合
cbind 按列组合
nrow(m) 矩阵的行数
ncol(m) 矩阵的列数
colnames(m) 给矩阵列命名
array 多维数组，matrix为二维数组
apply(m, dim, func, flag) 对矩阵的每行或每列执行某个func

## 列表
list类似于字典，list可以递归
list() 创建list
names(l) 访问list的keys
unlist(l) 获得list的values
lapply(l, func) 对列表中的每个元素执行func
sapply(l, func) 对可以转换成矩阵或向量的list执行apply，可以直接输出一个矩阵
l$key 访问list元素的值

## 数据框
merge(x, y) 合并数据框

