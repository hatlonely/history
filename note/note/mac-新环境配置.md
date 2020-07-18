# Mac 新环境配置

## 触摸设置

1. 轻点设置: 【系统偏好设置】 → 【触控板】 → 【光标与点按】 → 【轻点来点按】
2. 三指拖拽: 【系统偏好设置】 → 【辅助功能】 → 【指针控制】 → 【触控板选项】 → 【启用拖移】 → 【三指拖移】

## 开发环境

### xcode

应用商店搜索 xcode，安装

### git

``` sh
ssh-keygen
git config -g user.name "hatlonely"
git config -g user.email "hatlonely@gmail.com"
```

### iterm2

下载地址: <https://iterm2.com/downloads/stable/latest>

选中即复制: 【iTerm2】 → 【Preference】 → 【General】 → 【Selection】 → 【Copy to pasteboard on selection】

右键粘贴: 【iTerm2】 → 【Preference】 → 【Pointer】 → 【Bindings】 → 【Right button single click】 → 【Paste from clipboard】

lszrz 支持:

1. 安装 `szrz`: `brew install lszrz`
2. 下载脚本: `git clone https://github.com/xer0x/iterm2-zmodem.git`
3. 移动脚本到 PATH 目录: `cd iterm2-zmodem && cp iterm2-send-zmodem.sh /usr/local/bin && cp iterm2-recv-zmodem.sh /usr/local/bin`
4. 【iTerm2】 → 【Preference】 → 【Profiles】 → 【Advanced】→ 【Triggers】 → 【Edit】 → 【+】

| Regular expression    | Action               | Parameters                           |
| --------------------- | -------------------- | ------------------------------------ |
| `\*\*B0100`           | Run Silent Coprocess | /usr/local/bin/iterm2-send-zmodem.sh |
| `\*\*B00000000000000` | Run Silent Coprocess | /usr/local/bin/iterm2-recv-zmodem.sh |

### vscode

下载地址: <https://code.visualstudio.com/>

插件

- Markdown all in one: markdown 支持，`alt` + `shift` + `F` 格式化表格

### sublime text

下载地址: <https://download.sublimetext.com/Sublime%20Text%20Build%203211.dmg>

### brew

``` sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"

brew install go
brew install python3
brew install java
brew install cmake
brew install automake
brew install libtool
brew install wget
brew install pkg-config
```

### goland

下载地址: <https://www.jetbrains.com/go/>

## 常用软件

- chrome: 浏览器
- omnigraffle: 流程图
- alfred: 剪切板，快速调用
- istatistica: 监控

## google fonts(需要过墙)

下载地址: https://fonts.google.com/download?family=Roboto%20Mono|Inconsolata|Source%20Code%20Pro|Nanum%20Gothic%20Coding|PT%20Mono|Ubuntu%20Mono|Cousine|Fira%20Mono|Anonymous%20Pro|Oxygen%20Mono|Nova%20Mono|Fira%20Code


## 链接

- brew 官网: <https://brew.sh/>
- iterm2 官网: <https://www.iterm2.com/>
- sublime text 官网: <http://www.sublimetext.com/3>
- ZModem integration for iTerm 2: <https://github.com/xer0x/iterm2-zmodem>
- google fonts: <https://fonts.google.com/>
- vscode 官网: <https://code.visualstudio.com/>
- goland 官网: <https://www.jetbrains.com/go/>