// @file dota2_heroes_chinese.js
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2015-07-13
// @desc dota英雄信息爬虫
//  从http://www.dota2.com.cn/heroes/index.htm中获取各个英雄的子页面
//  再从各个子页面分析各个英雄的信息
// @note 依赖cheerio，获取cheerio: npm install cheerio -g

var http = require('http');
var url = require('url');
var events = require("events");
var cheerio = require('cheerio');

// http://www.dota2.com.cn/heroes/index.htm
var 英雄首页 = 'http://www.dota2.com.cn/heroes/index.htm';

function 英雄() {
    this.中文名 = '';
    this.英文名 = '';

    this.主属性 = '';
    this.力量属性 = 0;
    this.敏捷属性 = 0;
    this.智力属性 = 0;
    this.敏捷成长 = 0.0;
    this.力量成长 = 0.0;
    this.智力成长 = 0.0;
    this.最低攻击力 = 0;
    this.最高攻击力 = 0;
    this.攻击速度 = 0;
    this.攻击范围 = 0;
    this.护甲 = 0;
    this.移动速度 = 0;
    this.白天视野 = 0;
    this.晚上视野 = 0;
    this.弹道速度 = 0;

    this.攻击类型 = '';
    this.定位 = [];
    this.阵营 = '';
    this.其他名字 = [];

    this.故事背景 = '';
}

function 下载并分析页面(页面链接, 回调函数1, 回调函数2) {
    var 请求选项 = url.parse(页面链接);
    var 页面内容 = '';
    http.request(请求选项, function(响应包体) {
        响应包体.setEncoding('utf8');
        响应包体.on('data', function(数据) {
            页面内容 += 数据;
        }).on('end', function() {
            回调函数1(页面内容, 回调函数2);
        });
    }).on('error', function(err) {
        console.log('[error]:' + err.message);
    }).end();
}

// 获取各个英雄子页面
function 英雄首页分析回调函数(页面内容, 英雄页面分析回调函数) {
    var $ = cheerio.load(页面内容);
    $('a.heroPickerIconLink').each(function() {
        var 页面链接 = $(this).attr('href');
        下载并分析页面(页面链接, 英雄页面分析回调函数);
    });
}

// 处理各个英雄子页面
function 英雄页面分析回调函数(页面内容) {
    var $ = cheerio.load(页面内容);
    var 这个英雄 = new 英雄();

    {
        这个英雄.中文名 = $('div.top_hero_card>p>span').text();
        var 英雄名称 = $('div.top_hero_card>p').text();
        这个英雄.英文名 = 英雄名称.substring(
            英雄名称.indexOf(这个英雄.中文名) + 这个英雄.中文名.length);
    }

    {
        var 文本 = $('.info_ul').text().replace(/\s+/g, '')
        var 信息正则 = /攻击类型：([\s\S]+)定位：([\s\S]+)阵营：([\s\S]+)其他简称：([\s\S]+)/;
        if (信息正则.test(文本)) {
            var 匹配结果 = 信息正则.exec(文本);
            这个英雄.攻击类型 = 匹配结果[1];
            这个英雄.定位 = 匹配结果[2].replace(/-$/, '').split('-');
            这个英雄.阵营 = 匹配结果[3];
            这个英雄.其他名字 = 匹配结果[4].split('，')
        }
    }

    var 属性正则 = /(\d+)\s+\+\s+(\d+(\.\d+)*)/;
    {
        var 文本 = $('div#pro1').parent().text();
        if (属性正则.test(文本)) {
            var 匹配结果 = 属性正则.exec(文本);
            这个英雄.力量属性 = parseInt(匹配结果[1]);
            这个英雄.力量成长 = parseFloat(匹配结果[2]);
        }

        if (文本.indexOf('主要属性') != -1) {
            这个英雄.主属性 = '力量';
        }
    }

    {
        var 文本 = $('div#pro2').parent().text();
        if (属性正则.test(文本)) {
            var 匹配结果 = 属性正则.exec(文本);
            这个英雄.敏捷属性 = parseInt(匹配结果[1]);
            这个英雄.敏捷成长 = parseFloat(匹配结果[2]);
        }

        if (文本.indexOf('主要属性') != -1) {
            这个英雄.主属性 = '敏捷';
        }
    }

    {
        var 文本 = $('div#pro3').parent().text();
        if (属性正则.test(文本)) {
            var 匹配结果 = 属性正则.exec(文本);
            这个英雄.智力属性 = parseInt(匹配结果[1]);
            这个英雄.智力成长 = parseFloat(匹配结果[2]);
        }

        if (文本.indexOf('主要属性') != -1) {
            这个英雄.主属性 = '智力';
        }
    }

    {
        var 文本 = $('div#pro4').parent().text();
        var 攻速正则 = /攻击速度：(\d+)/;
        if (攻速正则.test(文本)) {
            var 匹配结果 = 攻速正则.exec(文本);
            这个英雄.攻击速度 = parseInt(匹配结果[1]);
        }
        var 攻击正则 = /攻击伤害：(\d+)-(\d+)/;
        if (攻击正则.test(文本)) {
            var 匹配结果 = 攻击正则.exec(文本);
            这个英雄.最低攻击力 = parseInt(匹配结果[1]);
            这个英雄.最高攻击力 = parseInt(匹配结果[2]);
        }
        var 攻击范围 = /攻击距离：(\d+)/;
        if (攻击正则.test(文本)) {
            var 匹配结果 = 攻击正则.exec(文本);
            这个英雄.攻击范围 = parseInt(匹配结果[1]);
        }
    }

    {
        var 文本 = $('div#pro5').parent().text();
        var 护甲正则 = /物理防御：(\d+)/;
        if (护甲正则.test(文本)) {
            var 匹配结果 = 护甲正则.exec(文本);
            这个英雄.护甲 = parseInt(匹配结果[1]);
        }
    }

    {
        这个英雄.移动速度 = $('div#pro6').parent().text().trim();
    }

    {
        var 文本 = $('div.area_box').text().replace(/\s+/g,'');
        var 视野正则 = /视野范围：(\d+)\/(\d+)/;
        if (视野正则.test(文本)) {
            匹配结果 = 视野正则.exec(文本);
            这个英雄.白天视野 = parseInt(匹配结果[1]);
            这个英雄.晚上视野 = parseInt(匹配结果[2]);
        }
        var 弹道正则 = /弹道速度：(\d+)/;
        if (弹道正则.test(文本)) {
            匹配结果 = 弹道正则.exec(文本);
            这个英雄.弹道速度 = parseInt(匹配结果[1]);
        }
    }

    这个英雄.故事背景 = $('div.story_box').text().trim();

    console.log(这个英雄);
}

下载并分析页面(英雄首页, 英雄首页分析回调函数, 英雄页面分析回调函数);

