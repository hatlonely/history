# ESL和ETPL


## ESL(Enterprise Standard Loader)

ESL是一个浏览器端，符合AMD标准的加载器，适用于现代浏览器端应用程序的入口和模块管理
ESL和RequireJS相比具有更小的体积、更高的性能、只能在浏览器端运行、不支持shim配置项

ESL Hello world
    
1. 加载esl文件

    ```html
    <script src="http://s1.bdstatic.com/r/www/cache/ecom/esl/1-6-6/esl.js"></script>
    ```

2. 定义一个hello.js

    ```javascript
    define(function(require) {
        return function() {
         alert('hello world');
        }
    });
    ```

3. 使用esl加载hello.js

    ```javascript
    require(['hello'], function(hello) {
        hello();
    });
    ```

## ETPL(Enterprise Template)

ETPL是一个灵活的、具有强大复用功能的高性能的模板引擎，适用于Web前端应用中视图的生成，特别是SPA(Single Page App)类型的应用

```javascript
var etpl = require('etpl');
var render = etpl.compile('hello ${name}!');    // 编译模板源码
var text = render({name: 'etpl'});  // text = 'hello etpl'
```

### 语法

1. target: target-name 模板名
2. $(variable | filter | html | url | raw) 变量

    ```html
    <!-- target: helloWorld -->
    hello ${name}!
    ```

### 模板复用

1. import: targetName(master=masterName) 在当前位置插入target源码
2. master: masterName(master=parentMasterName) 母版名
3. contentplaceholder: contentName 模板中可被替换的内容
4. content: contentName 替换母版中的内容

    ```html
    <!-- master: parentMaster -->
    <div class="title">
        <!-- contentplaceholder: title -->
            title
        <!-- /contentplaceholder>
    </div>
    <div class="main"><!-- contentplaceholder: main --></div>

    <!-- target: targetForParentMaster(master=parentMaster) -->
    <!-- content: title -->
    target for parent master
    <!-- content: main -->
    <p>To build from within Xcode, you can use the WebKit workspace.</p>

    <!-- master: childMaster(master=parentMaster) -->
    <!-- content: title -->
    title for child
    <!-- content: main -->
    <div class="sidebar"><!-- contentplaceholder: sidebar --></div>
    <div class="article"><!-- contentplaceholder: article --></div>

    <!-- target: targetForChildMaster(master=childMaster) -->
    <!-- content: sidebar -->
    <ul class="navigator">...</ul>
    <!-- content: article -->
    <p>To build from within Xcode, you can use the WebKit workspace.</p>
    ```

5. use: targetName(data-name=expression, ...) 在当前位置插入target在render后的结果，允许静态或动态的数据项

    ```html
    <!-- target: info -->
    <p>name: $(name)<p>
    <p>email: $(email)<p>

    <!-- target: main -->
    <div class="info">
    <!-- use: info(name=${person.name}, email=${person.email})>
    </div>
    ```

### 条件与循环

1. if, elif, else 条件语句

    ```html
    <!-- if: $(number) > 0 -->
    $(number) greater than zero
    <!-- elif: $(number) < 0 -->
    $(number) lower than zero
    <!-- else -->
    zero
    <!-- /if -->
    ```

2. for: ${variable} as ${item} ${key} 循环语句

    ```html
    <ul>
        <!-- for: ${persons} as ${person}, ${key} -->
        <li>${key}: ${person.name}</li>
        <!-- /for -->
    </ul>
    ```

### API

addFilter, compile, config, get, getRender, parse, render

```javascript
var etpl = require('etpl');

etpl.addFilter('markdown', function(source, userExtra) {
    // source 输入字符串
    // userExtra 由用户自定义参数
    // 返回一个字符串
    // 使用方法 $(variable | markdown)
});

var render = etpl.compile(source)  // 编译源码

etpl.compile('<!--target: hello>hello ${name}');
etpl.get('hello')   // 从默认引擎中，根据target名称获取模板内容
// 从默认引擎中，根据target名称获取编译后的renderer函数
var helloRender = etpl.getRender('hello')

etpl.parse(source)  // 同compile，与老版本兼容，建议不用

// 使用默认引擎执行模板渲染，返回渲染后的字符串。
etpl.render('hello', {name: 'ETPL'})

var etplEngine = new etpl.Engine({
    commandOpen: '<%',
    commandClose: '%>'
});
```

## 参考资料

  - [esl说明](https://github.com/ecomfe/esl)
  - [etpl说明](https://github.com/ecomfe/etpl)