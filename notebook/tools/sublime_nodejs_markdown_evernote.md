# sublime text + nodejs markdown笔记


## nodejs配置

1. [nodejs官网](http://nodejs.org/)下载并安装node
2. 新建node工作目录node_workspace
3. 安装markdown解析工具[marked](https://github.com/chjj/marked)

    ```
    $ cd node_workspace
    $ npm install marked    // 安装marked

    // 检查是否安装成功
    $ node
    > var marked = require('marked');
    > console.log(marked('I am using __markdown__.'));
    // Outputs: <p>I am using <strong>markdown</strong>.</p>
    ```

4. 安装语法高亮工具[highlight.js](https://github.com/isagalaev/highlight.js)

    ```
    $ cd node_workspace
    $ npm install highlight.js
    ```

5. highlight.js还有很多css样式文件可以通过git下载，在src/styles目录下

    ```
    $ git clone https://github.com/isagalaev/highlight.js
    ```

## sublime配置

marked和highlight.js都是一些库，需要写一个简单的javascript程序（md2html.js）来讲markdown源码转成html，md2html.js输入md文件，输出html文件，运行命令`node md2html.js md1 ...`

- 配置编译环境，Tools -> Build System -> New Build System... -> 保存成markdown.sublime-build

    ```javascript@lineNum
    {
        "cmd": ["node", "G:/git_workspace/notebook/md2html.js", "$file",
                    // html输出路径
                    "-html_dir G:/node_workspace/notebook/",
                    // html图片路径
                    "-image_dir G:/git_workspace/notebook/image/",
                    // 基本样式
                    "-base_style G:/git_workspace/notebook/hatlonely-note.css",
                    // 代码样式
                    "-code_style G:/git_workspace/highlight.js/src/styles/xcode.css",
                    // 最后的个性签名
                    "-foot_image G:/git_workspace/notebook/hatlonely_footer.png",
                    "-evernote"     // evernote中的bug，代码前面加一个空格
        ],
        // 当编译环境为Automatic时，可以自动识别，但是貌似没用……
        "selector": "source.md",
        // chrome路径和node路径，注意分号之间不能有空格
        "path": "C:/Program Files (x86)/Google/Chrome/Application;E:/nodejs",
        "env": {
            // marked和highlight.js模块路径
            "NODE_PATH": "G:/node_workspace/node_modules"
        },

        // 这个用于运行
        "variants": [{
            "name": "run",
            "cmd": ["chrome", "G:/node_workspace/notebook/$file_base_name.html"]
        }]
    }
    ```
    
    编译系统好像不能自动识别md文件，得手动Tools -> Build System -> markdown

    这种编译方法windows由于编码原因不识别包含中文名称的md文件，如果不怕麻烦的话，在命令行里面还是可以编译中文名称的md文件的

- 配置快捷键ctrl-r，用chrome打开生成的html，Perferences -> Key Bindings User

    ```javascript
    [
        { "keys": ["ctrl+r"], "command": "build", "args": {"variant": "run"} }
    ]
    ```

## md2html.js

```javascript@lineNum
// @file   md2html.js
// @brief  parser markdown to html
// @author hatlonely
// @email  hatlonely@gmail.com

var fs = require('fs');
var marked = require('marked');
var hljs = require('highlight.js')

var config = {
    html_dir: './',
    image_dir: '../image/',
    base_style: '../hatlonely-note.css',
    code_style: '../../highlight.js/src/styles/xcode.css',
    foot_image: '../drawhl.js',
    evernote: false
}

var renderer = function () {
    var renderer = new marked.Renderer();

    function escapeHTML(str) {
        return ('' + str).replace(/&/g, '&amp;').replace(/</g, '&lt;')
            .replace(/>/g, '&gt;').replace(/"/g, '&quot;');
    };

    renderer.code = function (code, lang) {
        if (lang == undefined) {
            lang = 'nolang';
        }

        if (config.evernote) {
            lang += '@space';
        }

        var langParam = lang.split('@');
        lang = langParam[0];
        langParam = langParam.splice(1);

        var hlcode = '';
        try {
            hlcode = hljs.highlight(lang, code).value;
        } catch (e) {
            hlcode = escapeHTML(code);
        }

        var hlcodeArray = hlcode.split('\n');
        var numLines = hlcodeArray.length;
        var lineNumWidth = numLines.toString().length;

        for (var paramIndex = 0; paramIndex < langParam.length; paramIndex++) {
            switch (langParam[paramIndex]) {
            case 'lineNum':
                hlcode = '';
                for (var hlcodeIndex = 0; hlcodeIndex < numLines; hlcodeIndex++) {
                    var curLineNum = hlcodeIndex + 1;
                    var indexWidth = curLineNum.toString().length;
                    for (var i = 0; i < lineNumWidth - indexWidth; i++) {
                        curLineNum = ' ' + curLineNum;
                    }
                    hlcodeArray[hlcodeIndex] = '<span class="linenum">'
                        + curLineNum + '</span>  ' 
                        + hlcodeArray[hlcodeIndex];
                }
                break;
            case 'space':
                for (var hlcodeIndex = 0; hlcodeIndex < numLines; hlcodeIndex++) {
                    hlcodeArray[hlcodeIndex] = ' ' + hlcodeArray[hlcodeIndex];
                }
                break;
            }
        }
        hlcode = hlcodeArray.join('\n');

        return ''
            + '<pre><code class="hljs ' + lang + '">' 
            + hlcode + '\n'
            + '</code></pre>';
    }

    renderer.image = function (href, title, text) {
        return ''
            + '<div class="image"><img src="' + config.image_dir
            + href + '" alt="' + text + '"></div>';
    }

    return renderer;
}();

marked.setOptions({
  renderer: renderer,
  gfm: true,
  tables: true,
  breaks: true,
  pedantic: true,
  sanitize: true,
  smartLists: true,
  smartypants: true,
});

function makeHeader(title) {
    return ''
        + '<!DOCTYPE html>' + '\n'
        + '<meta charset="UTF-8">' + '\n'
        + '<title>' + title + '</title>' + '\n'
        + '<style type="text/css">' + '\n'
        + '    @import url(' + config.base_style + ');' + '\n'
        + '    @import url(' + config.code_style + ');' + '\n'
        + '</style>' + '\n'
        + '<script type="text/javascript" src="' + config.foot_image + '"></script>' + '\n';
}

function makeFooter() {
    return ''
        + '<footer>' + '\n'
        + '    <img id="hatlonely" />' + '\n'
        + '</footer>' + '\n';
}

function md2html(md_path, html_path, header, footer) {
    fs.readFile(md_path, 'utf-8', function (err, data) {
        if (err) {
            console.log(err);
        } else {
            fs.writeFile(html_path, header + marked(data) + footer, 'utf-8');
        }
    });
}



function main() {
    var arguments = process.argv.splice(2);
    markdownFiles = [];
    for (var argIndex = 0; argIndex < arguments.length; argIndex++) {
        var argument = arguments[argIndex];
        if (argument.slice(0, 1) == '-') {
            var kv = argument.slice(1).split(/\s/);
            var key = kv[0];
            var value = kv[1];
            switch (key) {
            case 'html_dir':
            case 'image_dir':
            case 'base_style':
            case 'code_style':
            case 'foot_image':
                if (fs.existsSync(value)) {
                    config[key] = value;
                }
                break;
            case 'evernote':
                config.evernote = true;
                break;
            default:
                break;
            }
        } else {
            markdownFiles = argument.split(/\s/);
        }
    }

    for (var key in markdownFiles) {
        var html_dir = config.html_dir;
        var header = '';
        var footer = '';

        var md_path = markdownFiles[key];
        var startIndex = md_path.lastIndexOf('/');
        var endIndex = md_path.lastIndexOf('.');
        if (startIndex == -1) {
            startIndex = md_path.lastIndexOf('\\');
        }
        if (endIndex <= startIndex) {
            endIndex = md_path.length;
        }

        var filename = md_path.substring(startIndex + 1, endIndex);
        header = makeHeader(filename);
        footer = makeFooter();

        html_path = html_dir + filename + '.html';
        md2html(md_path, html_path, header, footer);
    }
}

main();
```

## 链接

- [nodejs官网](http://nodejs.org/)
- [highlightjs官网](http://highlightjs.org/)
- [marked git地址](https://github.com/chjj/marked)
- [highlightjs git地址](https://github.com/isagalaev/highlight.js)
- [sublime text编译](http://sublimetext.info/docs/en/reference/build_systems.html)