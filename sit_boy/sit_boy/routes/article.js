var express = require('express');
var router = express.Router();

// get markdown page
router.get('/', function(req, res) {
    var md_home = './public/documents/'
    var document = req.query['doc'];
    var title = document;
    res.render('article', {
        title: title,
        document: document,
    });

});

module.exports = router;
