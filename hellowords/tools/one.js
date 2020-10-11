//
//  one.js
//
//
//  Created by hatlonely on 15/9/16.
//
//
//  从 http://wufazhuce.com/one/vol.$i 爬取每日一言
//
//

var fs      = require('fs');
var cheerio = require('cheerio');
var request = require('request');
var async   = require('async');

var ones = [];
var dateStart = new Date('2012/10/7');
var dateToday = new Date();
var count = parseInt((dateToday - dateStart) / 1000 / 60 / 60 / 24);

var start = fs.readFileSync('../data/one.meta', 'utf-8');

function analysis(error, response, body) {
    if (!error && response.statusCode == 200) {
        var $ = cheerio.load(body);
        var url = response.request.uri.href;
        // 格式: index | sentence
        ones.push(''
            + url.substring(url.lastIndexOf('.') + 1, url.length)
            + '\t'
            + $('.one-cita').text().replace(/^\s+/, '').replace(/\s+$/, ''));
        if (ones.length >= (count - start)) {
            // 写入数据
            for (var i in ones) {
                fs.appendFileSync('../data/one.txt', ones[i] + '\n', 'utf-8');
            }
            // 记录当前下载的数目
            fs.writeFileSync('../data/one.meta', count, 'utf-8');
        }
    } else {
        console.log('failed. please retry.');
    }
}

for (var i = start; i < count; i++) {
    url = 'http://wufazhuce.com/one/vol.' + i;
    request(url, analysis);
}
