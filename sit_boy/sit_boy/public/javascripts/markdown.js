// this file translate markdown to html format using marked
// and highlight the code using highlight.js
// the markdown content is from div.#markdown

function escapeHTML(str) {
    return ('' + str)
        .replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;')
        .replace(/"/g, '&quot;');
}

function decodeHTML(str) {
    return ('' + str)
        .replace(/&amp;/g,'&')
        .replace(/&gt;/g,'>')
        .replace(/&lt;/g,'<')
        .replace(/&quot;/g,'"');
}

var renderer = function () {
    var renderer = new marked.Renderer();

    renderer.paragraph = function (text) {
        if (/&lt;!--.*?--&gt;/.test(text)) {
            return decodeHTML(text);
        }
        return '<p>' + text  + '</p>';
    }

    renderer.code = function (code, lang) {
        if (lang == undefined) {
            lang = 'nolang';
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
                    hlcodeArray[hlcodeIndex] = ''
                        + '<span class="linenum">'
                        + curLineNum
                        + '</span>  '
                        + hlcodeArray[hlcodeIndex];
                }
                break;
            default:
                break;
            }
        }
        hlcode = hlcodeArray.join('\n');

        return ''
            + '<pre><code class="hljs ' + lang + '">'
            + hlcode + '\n'
            + '</code></pre>';
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


