package article_mysql

import (
	"database/sql"
	_ "github.com/go-sql-driver/mysql"
)

type ArticleMysql struct {
	db *sql.DB
}

type Article struct {
	Id    int
	Title string
	Views int
}

func (a *ArticleMysql) Init(uri string, maxIdleConn int, maxOpenConn int) error {
	db, err := sql.Open("mysql", uri)
	if err != nil {
		return err
	}
	db.SetMaxOpenConns(maxOpenConn)
	db.SetMaxIdleConns(maxIdleConn)
	if err := db.Ping(); err != nil {
		return err
	}
	a.db = db
	return nil
}

func (a *ArticleMysql) SelectArticle() ([]*Article, error) {
	var articles []*Article

	rows, err := a.db.Query(`SELECT id, title, views FROM article ORDER BY views`)
	if err != nil {
		return nil, err
	}
	for rows.Next() {
		article := &Article{}
		if err := rows.Scan(&article.Id, &article.Title, &article.Views); err != nil {
			return nil, err
		}
		articles = append(articles, article)
	}

	return articles, nil
}

func (a *ArticleMysql) ViewArticle(title string) error {
	_, err := a.db.Exec(`INSERT INTO article (title, views) VALUES (?, 1) ON DUPLICATE KEY UPDATE views=views+1`, title)
	return err
}
