package markdown

import (
	"io/ioutil"
	"gopkg.in/gin-gonic/gin.v1"
	"net/http"
	"strings"
	"net/url"
	"article_mysql"
)

type Markdown struct {
	dirname string
	db *article_mysql.ArticleMysql
}

func (m *Markdown) Init(dirname string, db *article_mysql.ArticleMysql) error {
	m.dirname = dirname
	m.db = db

	return nil
}

type DocInfo struct {
	Url   string `json:"url"`
	Doc   string `json:"doc"`
	Views int    `json:"views"`
}

func (m *Markdown) ListHandler(ctx *gin.Context) {
	ctx.Header("Access-Control-Allow-Origin", "*")

	infos, err := ioutil.ReadDir(m.dirname)
	if err != nil {
		ctx.String(http.StatusInternalServerError, err.Error())
	}

	var doclist []DocInfo

	articles, err := m.db.SelectArticle()
	if err != nil {
		// nothing to do
	}

	titleViews := map[string]int{}
	for _, article := range articles {
		titleViews[article.Title] = article.Views
	}

	for _, info := range infos {
		if info.IsDir() {
			continue
		}
		if strings.HasSuffix(info.Name(), ".md") {
			doc := info.Name()[0:len(info.Name())-3]
			views := 0
			if val, ok := titleViews[doc]; ok {
				views = val
			}
			doclist = append(doclist, DocInfo{
				Url: "/article?doc=" + url.QueryEscape(doc),
				Doc: doc,
				Views: views,
			})
		}
	}

	ctx.JSON(http.StatusOK, doclist)
}

func (m *Markdown) DocsHandler(ctx *gin.Context) {
	ctx.Header("Access-Control-Allow-Origin", "*")

	basename := ctx.Query("doc")
	filename := m.dirname + basename + ".md"
	docbytes, err := ioutil.ReadFile(filename)

	m.db.ViewArticle(basename)

	if err != nil {
		ctx.String(http.StatusNotFound, "404 not found")
		return
	}

	ctx.String(http.StatusOK, string(docbytes))
}
