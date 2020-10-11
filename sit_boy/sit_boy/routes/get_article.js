var express = require('express');
var router = express.Router();

// get markdown page
router.get('/', function(req, res) {
    var md_home = './public/documents/'
    var doc = req.query['doc'];
    var title = doc;
    require('fs').readFile(md_home + doc + '.md', 'utf-8', function(err, markdown) {
        if (err) {
            res.send({
                markdown: doc + ' not found'
            })
        } else {
            res.send({
                markdown: markdown
            });
        }
    });
});

module.exports = router;
