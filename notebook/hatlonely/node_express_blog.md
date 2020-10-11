# 博客网站

## http

```javascript@lineNum
var http = require('http');

http.createServer(function (req, res) {
    res.writeHead(200, {
        'Content-type': 'text/html'
    });
    res.write('<h1>Node.js</h1>');
    res.end('<p>Hello world</p>');
}).listen(3000);
```

## 安装express

```
$ npm install express
$ express --help
```