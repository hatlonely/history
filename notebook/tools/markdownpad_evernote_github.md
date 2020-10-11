# MarkdownPad + Evernote + Github 个人笔记


## 简介

用markdown写笔记，用github来管理markdown源码，把生成的笔记保存到evernote里方便阅读

- 记笔记的时候更关心内容，并不太关注样式  =>  markdown
- 读笔记的时候很注重可读性，所以样式很重要  =>  evernote
- 笔记较多，需要分类管理  =>  github

## 环境搭建

1. 安装[MarkdownPad](http://markdownpad.com/)，安装[Evernote](http://evernote.com/intl/zh-cn/evernote/)，安装[Github客户端](https://github.com/)
2. 在github网站上创建一个新的repository（假设名字为notebook）
3. 打开git sehell

    ```
    $ git clone git@github.com/user/notebook
    ```

## 新建和修改笔记

1. 打开markdownpad，新建或打开文档note.md保存到notebook目录下
2. 编辑note.md
3. 导出成note.html（快捷键ctrl-shift-1）
4. 用浏览器（建议chrome）打开note.html
5. 全选，复制，粘贴到evernote中
6. 保存笔记源码到github上

    ```
    $ cd notebook
    $ git pull -a
    $ git add note.md
    $ git commit -m "add note"
    $ git push origin master
    ```

直接复制markdown中的笔记到evernote中是没有样式的，必须导成html后复制

## 样式

1. 在notebook目录下创建一个css样式文件，在里面定义你的样式

    建议用其他的样式修改比如：
    - markdownpad里的工具 -> 选项 -> 样式表里面的样式
    - <https://github.com/hatlonely/notebook>里的hatlone-note.css

2. 在工具 -> 选项 -> 样式表 -> none -> 编辑，引用刚刚创建的css，`@import url(css_path);`

    ```
    @import url(D:/github-workspace/notebook/hatlonely-note.css);
    ```

## 分享

好东西当然要分享啦，evernote里面有分享哦，也可以直接共享github上的源码，还可以根据自己样式来重新生成笔记哦！^_^

## 链接

- [MarkdownPad官网](http://markdownpad.com/)
- [Evernote官网](http://evernote.com/intl/zh-cn/evernote/)
- [Github官网](https://github.com/)