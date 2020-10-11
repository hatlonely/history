# sublime text


##  列编辑模式

1. 鼠标右键+shift
2. Ctlr+Shift+上下箭头 

## 常用快捷键

- 查找：ctrl + f
- 替换：ctrl + h
- 全局查找：ctrl + shift + f
- 全局替换：ctrl + shift + h
- 快速注释：ctrl + /
- 编译：ctrl + b

## 插件安装方法

1. 按Ctrl+`调出console
2. 粘贴以下代码到底部命令行并回车：
    import urllib2,os;pf='Package Control.sublime-package';ipp=sublime.installed\_packages\_path();os.makedirs(ipp) if not os.path.exists(ipp) else None;open(os.path.join(ipp,pf),'wb').write(urllib2.urlopen('http://sublime.wbond.net/'+pf.replace(' ','%20')).read())
3. 重启Sublime Text 2
4. 如果在Perferences->package settings中看到package control这一项，则安装成功
5. 按下Ctrl+Shift+P调出命令面板
6. 输入install 调出 Install Package 选项并回车，然后在列表中选中要安装的插件

## 插件卸载

1. ctr + shift + P，输入package
2. 查找remove package

## 插件

```
1. zen coding
package control => emmet

2. js format
package control => js format
右键 -> js_format

3. alignment
package control => alignment
选择 -> <ctrl-alt-a>

4. tag
package control => tag
Edit -> Tag -> Auto-Format Tags 或者 右键 -> Auto-Format Tags

5. AndyJS2
package control => AndyJS2
```

## 编译

Tools -> Build System -> New Build System...

```javascript
{
  "cmd": ["python", "-u", "$file"],
  "file_regex": "^[ ]*File \"(...*?)\", line ([0-9]*)",
  "selector": "source.python"
}

cmd           必须，命令
file_regex    捕捉错误输出的正则表达式
line_regex    file_regex未匹配，用line_regex匹配
selector      选择合适的编译环境
working_dir   工作目录
encoding      cmd的输出编码，默认为UTF-8
target        运行命令，默认为 exec (Package/Default/exec.py)
env           环境变量
shell         如果true，cmd将在一个shell中运行
path          替换当前的PATH变量
```

## 参考

  - [sublime text官网](http://www.sublimetext.com/)
  - [sublime text编译](http://sublimetext.info/docs/en/reference/build_systems.html)