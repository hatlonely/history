var http = require('http');
var fs   = require('fs');

var onesContext = fs.readFileSync('../data/one.txt', 'utf-8');
var onesLines = onesContext.split('\n');
for (var i in onesLines) {
    onesLines[i] = onesLines[i].split('\t')[1];
}

var server = http.createServer(function (request, response) {
    try {
        response.writeHead(404, {"Content-Type": "text/plain"});
        response.write(onesLines[parseInt(Math.random() * (onesLines.length - 1))]);
        response.end();
    } catch (error) {
        // nothing to do
    }
});

server.listen(8888);
