// @file china_area_spider.js
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2015-07-16
// @desc 从http://www.ip138.com/post/爬取中国各个地区邮编区号信息

var cheerio = require('cheerio');       // nodejs端jquery库
var request = require('request');       // 对http.request封装
var async   = require('async');         // 异步框架
var iconv   = require('iconv-lite');    // 编码转换

async.waterfall([downloadFirstPage, analysisFirstPage], finish);

function downloadFirstPage(callback) {
    download('http://www.ip138.com/post/', callback);
}

function analysisFirstPage(content, callback) {
    var links = analysisFirstPageAndGetLinks(content);

    function finish(error, result) {
        if (error) {
            callback(error);
        } else {
            callback(null, result);
        }
    }

    // 对于每一个链接执行analysisCityPage，并将结果汇总到finish中
    async.map(links, analysisCityPage, finish);
}

function finish(error, result) {
    if (error) {
        console.log('[error] ' + error);
    } else {
        saveInfomation(result);
    }
}

function analysisCityPage(link, callback) {
    function downloadPage(callback) {
        download(link, callback);
    }

    function finish(error, result) {
        var information = analysisCityPageAndGetInfomation(result);

        if (error) {
            callback(error);
        } else {
            callback(null, information);
        }
    }

    // 下载省份信息页面，然后分析页面获取，城市，邮编，区号等信息
    async.waterfall([downloadPage], finish);
}

function download(link, callback) {
    var datas = [];
    var length = 0;
    request(link, function (error, response) {
        if (error || response.statusCode != 200) {
            callback('error or statusCode != 200', null);
        } else {
            var buffer = new Buffer(length);
            var position = 0;
            for (var i = 0; i < datas.length; i++) {
                datas[i].copy(buffer, position);
                position += datas[i].length;
            }
            callback(error, iconv.decode(buffer, 'gbk'));
        }
    }).on('data', function (data) {
        // gbk的页面，需要将数据缓存下来，之后需要拼接在一起解码
        datas.push(data);
        length += data.length;
    });
}

// 分析第一页，获取各个省信息链接
function analysisFirstPageAndGetLinks(content) {
    var $ = cheerio.load(content);
    var links = [];

    $('div#newAlexa a').each(function () {
        links.push('http://www.ip138.com' + $(this).attr('href'));
    });

    return links;
}

// 分析各个省页面，获取省信息
function analysisCityPageAndGetInfomation(content) {
    var $ = cheerio.load(content);

    var information = {};
    information['province'] = '';
    information['cities'] = {};

    var text = $('center h2 div').text();
    information['province'] = text.substring(0, text.indexOf('邮编'));

    var cityname = information['province'];
    $('table.t12 tr').each(function () {
        // 表头
        if ($(this).attr('class')) {
            return;
        }

        var text = $(this).text();
        if (!text) {
            return;
        }

        var td = $(this).find('td');

        // 城市
        if ($(this).find('b').text()) {
            var city = {
                'city'    : td.eq(0).text(),
                'areas'   : [],
                'zipCode' : td.eq(1).text(),
                'areaCode': td.eq(2).text(),
            };
            cityname = city['city'];
            information['cities'][cityname] = city;
            return;
        }

        var city = information['cities'][cityname];
        // 直辖市
        if (!city) {
            cityname = information['province'];
            city = {
                'city': cityname,
                'areas': [],
            }
            information['cities'][cityname] = city;
        }

        // 地区
        if (td.length == 6) {
            var area1 = {
                'area'    : td.eq(0).text(),
                'city'    : cityname,
                'zipCode' : td.eq(1).text(),
                'areaCode': td.eq(2).text(),
            };
            city['areas'].push(area1);
            if (td.eq(3).text().replace(/\s+/, '')) {
                var area2 = {
                    'area'    : td.eq(3).text(),
                    'city'    : cityname,
                    'zipCode' : td.eq(4).text(),
                    'areaCode': td.eq(5).text(),
                };
                city['areas'].push(area2);
            }
        } else if ($td.length == 4) {
            var area = {
                'area'    : td.eq(0).text(),
                'city'    : cityname,
                'zipCode' : td.eq(1).text(),
                'areaCode': td.eq(2).text(),
            };
            city['areas'].push(area);
        } else {
            console.log('invalid text: ' + text);
            return null;
        }
    });

    return information;
}

// 保存信息，sql格式
function saveInfomation(informations) {
    var provinceSqls = [];
    var citySqls     = [];
    var areaSqls     = [];
    var provinceId   = 1;
    var cityId       = 1;
    var areaId       = 1;
    for (var i in informations) {
        // 省
        var provinceSql = 'INSERT INTO province (`province_id`, `province_name`) VALUES ('
            + provinceId + ', \'' + informations[i]['province'] + '\'' + ');';
        provinceSqls.push(provinceSql);

        // 市
        var cities = informations[i]['cities'];
        for (var j in cities) {
            var citySql = 'INSERT INTO city (`city_id`, `province_id`, `city_name`) VALUES ('
                + cityId + ', ' + provinceId + ', \'' + j + '\');';
            citySqls.push(citySql);

            var areas = cities[j]['areas'];
            if (areas.length == 0) {
                var areaSql = 'INSERT INTO area (`area_id`, `city_id`, `area_name`, '
                    + '`zip_code`, `area_code`) VALUES (' + areaId + ', ' + cityId + ', '
                    + '\'' + j + '\', ' + '\'' + cities[j]['zipCode'] + '\', '
                    + '\'' + cities[j]['areaCode'] + '\');';

                areaSqls.push(areaSql);
                areaId++;
            } else {
                for (var i in areas) {
                    var areaSql = 'INSERT INTO area (`area_id`, `city_id`, `area_name`, '
                        + '`zip_code`, `area_code`) VALUES (' + areaId + ', ' + cityId + ', '
                        + '\'' + areas[i]['area'] + '\', ' + '\'' + areas[i]['zipCode'] + '\', '
                        + '\'' + areas[i]['areaCode'] + '\');';
                    areaSqls.push(areaSql);
                    areaId++;
                }
            }
            cityId++;
        }
        provinceId++;
    }
    console.log(provinceSqls.join('\n'));
    console.log(citySqls.join('\n'));
    console.log(areaSqls.join('\n'));
}
