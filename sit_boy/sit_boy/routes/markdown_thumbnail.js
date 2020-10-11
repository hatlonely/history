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

            thumbnails_html += '<h2> ' + title + ' </h2>\n'
            thumbnails_html += '<p> ' + brief + ' </p>\n'
            thumbnails_html += ''
                + '<p> <a class="btn" href="/article?doc='
                + markdowns[index].substring(0, markdowns[index].length - 3)
                + '">查看原文 »</a> </p>\n'
        }
    }

    console.log(thumbnails_html);
    return thumbnails_html;
}

make_thumbnail('../public/documents');
