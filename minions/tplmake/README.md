# lhtools

## tplmake.py
tplmake.py是一个模板生成工具，支持的模板存在template包中以`{tpl_name}_tpl.py`命名
tplmake.py可以拓展自己的template，`{tpl_name}_tpl.py` 必须实现如下三个函数
`tpls()` 返回模板内的模板字符串列表
`outs()` 返回模板输出的文件名列表
`params(options)` 接受命令行参数，返回模板字符串所需的参数字典

目前支持的模板有:
* `cmakelists_tpl.py`，cmake模板
* `cppclass_tpl.py`，c++类模板
* `leetcpp_tpl.py`，leetcode c++模板
* `leetjava_tpl.py`，leetcode java模板

``` bash
tplmake.py -h
tplmake.py -t leetcpp -h
tplmake.py -t cmakelists -h
```
