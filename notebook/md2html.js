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

    renderer.code2 = function (code, lang) {
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

        for (var hlcodeIndex = 0; hlcodeIndex < numLines; hlcodeIndex++) {
            hlcodeArray[hlcodeIndex] = '<td><pre>' + hlcodeArray[hlcodeIndex] + '</pre></td>';
        }
        for (var paramIndex = 0; paramIndex < langParam.length; paramIndex++) {
            switch (langParam[paramIndex]) {
            case 'lineNum':
                hlcode = '';
                for (var hlcodeIndex = 0; hlcodeIndex < numLines; hlcodeIndex++) {
                    var curLineNum = hlcodeIndex + 1;
                    hlcodeArray[hlcodeIndex] = '<td><span class="linenum">'
                        + curLineNum + '</span></td>' 
                        + hlcodeArray[hlcodeIndex];
                }
                break;
            }
        }
        for (var hlcodeIndex = 0; hlcodeIndex < numLines; hlcodeIndex++) {
            hlcodeArray[hlcodeIndex] = '<tr>' + hlcodeArray[hlcodeIndex] + '</tr>';
        }
        hlcode = hlcodeArray.join('\n');

        return ''
            + '<table>' 
            + hlcode + '\n'
            + '</table>';
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
        + '<link rel="stylesheet" href="' + config.base_style + '" />' + '\n'
        + '<link rel="stylesheet" href="' + config.code_style + '" />' + '\n'
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
                config[key] = value;
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
        if (endIndex < startIndex) {
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