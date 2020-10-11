// @file dota2_heroes.js
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2015-07-13
// @desc dota英雄信息爬虫
//  从http://www.dota2.com.cn/heroes/index.htm中获取各个英雄的子页面
//  再从各个子页面分析各个英雄的信息
// @note 依赖cheerio，获取cheerio: npm install cheerio -g

var http    = require('http');
var url     = require('url');
var cheerio = require('cheerio');
var mysql   = require('mysql');

// http://www.dota2.com.cn/heroes/index.htm
var index = 'http://www.dota2.com.cn/heroes/index.htm';

var connectionPool = mysql.createPool({
    connectionLimit: 10,
    host: 'localhost',
    user: 'hatlonely',
    password: '123456',
    database: 'dota2'
});

function Hero() {
    this.chineseName       = '';    // 中文名
    this.englishName       = '';    // 英文名

    this.mainProperty      = '';    // 主属性类型
    this.strength          = 0;     // 力量属性
    this.dexterity         = 0;     // 敏捷属性
    this.intelligence      = 0;     // 智力属性
    this.strengthInc       = 0.0;   // 力量成长
    this.dexterityInc      = 0.0;   // 敏捷成长
    this.intelligenceInc   = 0.0;   // 智力成长
    this.attackMin         = 0;     // 最低攻击力
    this.attackMax         = 0;     // 最高攻击力
    this.attackSpeed       = 0;     // 攻击速度
    this.attackRange       = 0;     // 攻击范围
    this.armor             = 0;     // 护甲
    this.movingSpeed       = 0;     // 移动速度
    this.visualFieldDay    = 0;     // 白天视野
    this.visualFieldNight  = 0;     // 晚上视野
    this.ballisticVelocity = 0;     // 弹道速度

    this.attackType        = '';    // 攻击类型
    this.position          = [];    // 定位
    this.camp              = '';    // 阵营
    this.otherName         = [];    // 其他名字

    this.story             = '';    // 故事背景

    // images
    this.icon              = '';    // 英雄图标
    this.vert              = '';    // 大图标
    this.bigImage          = '';    // 大图

    this.abalities         = [];    // 技能
}

function Abality() {
    this.hero          = '';
    this.chineseName   = '';        // 技能名称
    this.icon          = '';        // 图标
    this.idx           = 0;         // 技能位置
    this.detail        = '';        // 说明
    this.notice        = '';        // 注意
    this.effect        = {};        // 效果
    this.scepterEffect = {};        // A杖效果
}

function downloadAndAnalysisPage(pageUrl, callback1, callback2) {
    var options = url.parse(pageUrl);
    var content = '';
    http.request(options, function(response) {
        response.setEncoding('utf8');
        response.on('data', function(html) {
            content += html;
        }).on('end', function() {
            callback1(content, callback2);
        });
    }).on('error', function(err) {
        console.log('[error]:' + err.message);
    }).end();
}

// 获取各个英雄子页面
function indexCallback(content, callback) {
    var $ = cheerio.load(content);
    $('a.heroPickerIconLink').each(function() {
        var page = $(this).attr('href');
        downloadAndAnalysisPage(page, callback);
    });
}

// 处理各个英雄子页面
function heroesCallback(content) {
    var $ = cheerio.load(content);
    var hero = new Hero();

    {
        hero.chineseName = $('div.top_hero_card>p>span').text();
        var name = $('div.top_hero_card>p').text();
        hero.englishName = name.substring(
            name.indexOf(hero.chineseName) + hero.chineseName.length);
    }

    {
        var text = $('.info_ul').text().replace(/\s+/g, '')
        var infoRegex = /攻击类型：([\s\S]+)定位：([\s\S]+)阵营：([\s\S]+)其他简称：([\s\S]+)/;
        if (infoRegex.test(text)) {
            var matchResult = infoRegex.exec(text);
            hero.attackType = matchResult[1];
            hero.position = matchResult[2].replace(/-$/, '').split('-');
            hero.camp = matchResult[3];
            hero.otherName = matchResult[4].split('，')
        }
    }

    var propertyRegex = /(\d+)\s+\+\s+(\d+(\.\d+)*)/; {
        var text = $('div#pro1').parent().text();
        if (propertyRegex.test(text)) {
            var matchResult = propertyRegex.exec(text);
            hero.strength = parseInt(matchResult[1]);
            hero.strengthInc = parseFloat(matchResult[2]);
        }

        if (text.indexOf('主要属性') != -1) {
            hero.mainProperty = '力量';
        }
    }

    {
        var text = $('div#pro2').parent().text();
        if (propertyRegex.test(text)) {
            var matchResult = propertyRegex.exec(text);
            hero.dexterity = parseInt(matchResult[1]);
            hero.dexterityInc = parseFloat(matchResult[2]);
        }

        if (text.indexOf('主要属性') != -1) {
            hero.mainProperty = '敏捷';
        }
    }

    {
        var text = $('div#pro3').parent().text();
        if (propertyRegex.test(text)) {
            var matchResult = propertyRegex.exec(text);
            hero.intelligence = parseInt(matchResult[1]);
            hero.intelligenceInc = parseFloat(matchResult[2]);
        }

        if (text.indexOf('主要属性') != -1) {
            hero.mainProperty = '智力';
        }
    }

    {
        var text = $('div#pro4').parent().text();
        var attackSpeedRegex = /攻击速度：(\d+)/;
        if (attackSpeedRegex.test(text)) {
            var matchResult = attackSpeedRegex.exec(text);
            hero.attackSpeed = parseInt(matchResult[1]);
        }
        var attackRegex = /攻击伤害：(\d+)-(\d+)/;
        if (attackRegex.test(text)) {
            var matchResult = attackRegex.exec(text);
            hero.attackMin = parseInt(matchResult[1]);
            hero.attackMax = parseInt(matchResult[2]);
        }
        var attackRange = /攻击距离：(\d+)/;
        if (attackRegex.test(text)) {
            var matchResult = attackRegex.exec(text);
            hero.attackRange = parseInt(matchResult[1]);
        }
    }

    {
        var text = $('div#pro5').parent().text();
        var armorRegex = /物理防御：(\d+)/;
        if (armorRegex.test(text)) {
            var matchResult = armorRegex.exec(text);
            hero.armor = parseInt(matchResult[1]);
        }
    }

    {
        hero.movingSpeed = $('div#pro6').parent().text().trim();
    }

    {
        var text = $('div.area_box').text().replace(/\s+/g, '');
        var visualFieldRegex = /视野范围：(\d+)\/(\d+)/;
        if (visualFieldRegex.test(text)) {
            matchResult = visualFieldRegex.exec(text);
            hero.visualFieldDay = parseInt(matchResult[1]);
            hero.visualFieldNight = parseInt(matchResult[2]);
        }
        var ballisticVelocityRegex = /弹道速度：(\d+)/;
        if (ballisticVelocityRegex.test(text)) {
            matchResult = ballisticVelocityRegex.exec(text);
            hero.ballisticVelocity = parseInt(matchResult[1]);
        }
    }

    hero.story = $('div.story_box').text().trim();
    hero.icon = $('div.top_hero_card img').attr('src');
    hero.vert = $('div.hero_info img').attr('src');
    hero.bigImage = $('div.story_pic img').attr('src');

    {
        $('dl#focus_dl>dd').each(function() {
            var abality = new Abality();

            abality.idx = parseInt($(this).attr('jnxs'));
            abality.hero = hero.englishName;
            abality.icon = $(this).find('div.skill_wrap>img').attr('src');
            abality.chineseName = $(this).find('div.skill_info>p.skill_intro>span').text();
            abality.detail = $(this).find('div.skill_info>p.skill_intro').text()
                .replace(/\s+/, '').substring(abality.chineseName.length);
            abality.notice = $(this).find('div.skill_info>p.color_green').text();

            var effects = [];
            // 魔法消耗
            effects.push($(this).find('div.xiaohao_wrap>div.icon_xh').text());
            // 冷却时间
            effects.push($(this).find('div.xiaohao_wrap>div.icon_lq').text());

            $(this).find('ul.skill_ul>li').each(function() {
                var effect = $(this).text().replace(/\s+/, '');
                effects.push(effect);
            })

            for (var idx in effects) {
                var effect = effects[idx];
                var kv = effect.split('：');
                if (kv[0].indexOf('神杖') == -1) {
                    abality.effect[kv[0]] = kv[1];
                } else {
                    abality.scepterEffect[kv[0]] = kv[1];
                }
            }

            hero.abalities.push(abality);
        });
    }

    mysqlInsertHero(hero);
}

function mysqlInsertHero(hero) {
    var insertHeroSql =
        'INSERT INTO hero (`chinese_name`, `english_name`, `main_property`, `strength`, ' +
        '`dexterity`, `intelligence`, `strength_inc`, `dexterity_inc`, `intelligence_inc`, ' +
        '`attack_min`, `attack_max`, `attack_speed`, `attack_range`, `armor`, `moving_speed`, ' +
        '`visual_field_day`, `visual_field_night`, `ballistic_velocity`, `attack_type`, `position`, ' +
        '`camp`, `other_name`, `story`, `icon`, `vert`, `big_image`) VALUES (' +
        '?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)';

    var values = [hero.chineseName, hero.englishName, hero.mainProperty,
        hero.strength, hero.dexterity, hero.intelligence, hero.strengthInc,
        hero.dexterityInc, hero.intelligenceInc, hero.attackMin, hero.attackMax,
        hero.attackSpeed, hero.attackRange, hero.armor, hero.movingSpeed,
        hero.visualFieldDay, hero.visualFieldNight, hero.ballisticVelocity,
        hero.attackType, hero.position.join(','), hero.camp, hero.otherName.join(','), hero.story,
        hero.icon, hero.vert, hero.bigImage
    ];

    connectionPool.getConnection(function(error, connection) {
        if (error) {
            console.log(error);
            return;
        }

        // insert hero
        connection.query({
            sql: insertHeroSql,
            values: values,
            timeout: 40000
        }, function(error, result, fields) {
            connection.release();
            if (error) {
                console.log(error);
            }
            if (result) {
                connectionPool.getConnection(function(error, connection) {
                    if (error) {
                        console.log(error);
                    }
                    // query hero_id
                    connection.query({
                        sql: 'SELECT hero_id FROM hero WHERE english_name=?',
                        values: [hero.englishName],
                        timeout: 40000
                    }, function(error, result, fields) {
                        connection.release();
                        if (error) {
                            console.log(error);
                        }
                        if (result) {
                            var heroId = result[0].hero_id;
                            for (var idx in hero.abalities) {
                                var abality = hero.abalities[idx];
                                // insert abality
                                mysqlInsertAbality(heroId, abality);
                            }
                        }
                    });
                });
            }
        });
    });
}

function mysqlInsertAbality(heroId, abality) {
    connectionPool.getConnection(function(error, connection) {
        var insertAbalitySql =
            'INSERT INTO abality (`hero_id`, `idx`, `chinese_name`, `icon`, `detail`, ' +
            '`notice`, `effect`, `scepter_effect`) VALUES (?, ?, ?, ?, ?, ?, ?, ?)';
        var values = [heroId, abality.idx, abality.chineseName, abality.icon,
            abality.detail, abality.notice,
            JSON.stringify(abality.effect),
            JSON.stringify(abality.scepterEffect)
        ];
        connection.query({
            sql: insertAbalitySql,
            values: values,
            timeout: 40000
        }, function(error, result, fields) {
            connection.release();
            if (error) {
                console.log(error);
            }
        });
    });
}

downloadAndAnalysisPage(index, indexCallback, heroesCallback);

setTimeout(function() {
    connectionPool.end();
}, 5000);
