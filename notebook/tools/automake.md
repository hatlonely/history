# automake

## 下载安装

[http://ftp.gnu.org/gnu/]下载m4, autoconf, automake
解压和安装

```
$ ./configure ［--prefix=<path>］
$ make
$ make install  # 如果没有指定prefix，默认在/usr/local，需要root权限
```

## 源码

```bash
$ git clone git://git.sv.gnu.org/m4
$ git clone git://git.sv.gnu.org/autoconf
$ git clone git://git.sv.gnu.org/automake
```

## automake工作流程

![automake.png](automake.png)

## helloworld工程

helloworld目录下有3个文件，hello.h，hello.cpp，main.cpp，内容如下：

```cpp
// hello.h
extern void say_hello();

// hello.cpp
#include "hello.h"
#include <iostream>

void say_hello() {
    std::cout << "hello world" << std::endl;
}

// main.cpp
#include "hello.h"

int main() {
    say_hello();
}
```

1. 新建Makefile.am，并输入以下内容
    ```
    AUTOMAKE_OPTIONS=foreign
    bin_PROGRAMS=helloworld
    helloworld_SOURCES=hello.h hello.cpp main.cpp
    ```
2. 运行autoscan生产configure.scan
3. 重命名configure.scan为configure.ac，并作如下修改：
    ```
    AC_INIT(helloworld, 1.0, hatlonely@gmail.com)   # 修改，指定程序名称版本和bug提交地址
    AC_CONFIG_SRCDIR([hello.cpp])
    AM_INIT_AUTOMAKE    # 添加
    ```
4. 执行如下命令
    ```
    $ aclocal       # configure.ac -> aclocal.m4
    $ autoconf      # configure.ac + aclocal.m4 -> configure
    $ autoheader    # 生成config.h
    $ automake --add-missing --copy     # 生成缺失文件 Makefile.in
    $ ./configure   # Makefile.in + configure -> Makefile
    ```

## 链接

- [GNU 自由软件库](http://ftp.gnu.org/gnu/)
- [GNU M4](http://www.gnu.org/software/m4/m4.html)
- [Autoconf](http://www.gnu.org/software/autoconf/autoconf.html)
- [Automake](http://www.gnu.org/software/automake/automake.html)
- [Automake手册](http://www.gnu.org/software/automake/manual/automake.html)
- [Autoconf手册](http://www.gnu.org/software/autoconf/manual/autoconf.html)

