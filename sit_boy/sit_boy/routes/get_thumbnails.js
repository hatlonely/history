var express = require('express');
var router = express.Router();

var fs = require('fs');

function make_thumbnail(documents_path) {
    var files = fs.readdirSync(documents_path)
    var markdowns = [];
    if (files && files.length) {
        files.forEach(function(filename) {
            markdowns.push(filename);
        });
    }

    thumbnails_html = '';
    for (index in markdowns) {
        var data = fs.readFileSync(documents_path + '/' + markdowns[index], 'utf-8');
        if (data) {
            lines = data.split('\n');
            title = lines[0].substring(2);

            for (var i = 1; i < lines.length; i++) {
                if (lines[i].trim() == '' || lines[i].match('^<!--')) {
                    continue;
                } else {
                    brief = lines[i];
                    break;
                }
            }

            thumbnails_html += '<div class="col-md-4 column">\n'
            thumbnails_html += '<div class="thumbnail" data-url="/article?doc='
                            + markdowns[index].substring(0, markdowns[index].length - 3)
                            + '">\n'
            thumbnails_html += '<div class="thumbnail-title"> ' + title + ' </div>\n'
            thumbnails_html += '<div class="thumbnail-context"> ' + brief + ' </div>\n'
            thumbnails_html += '</div></div>\n'
        }
    }

    return thumbnails_html;
}

router.get('/', function(req, res) {
    res.send({
        thumbnails_html: make_thumbnail('./public/documents')
    });
});

module.exports = router;
