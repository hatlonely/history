var express = require('express');
var querystring = require('querystring');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/doclist', function(req, res, next) {
    doc = req.query.doc;
    res.render('doclist', {
        'title': doc,
        'url': 'http://123.207.136.97/webbe/doclist'
    });
});

router.get('/article', function(req, res, next) {
  doc = req.query.doc;
  res.render('article', {
    'title': doc,
    'url': 'http://123.207.136.97/webbe/md?' + querystring.encode({
      doc: req.query.doc
    })
  });
});

module.exports = router;
