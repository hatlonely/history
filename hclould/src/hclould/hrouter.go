package hclould

import (
	"github.com/cihub/seelog"
	"github.com/gin-gonic/gin"
	"github.com/spf13/viper"
	"net/http"
	"path/filepath"
	"strings"
)

type HRouter struct {
	router *gin.Engine

	markdown *Markdown
}

func (h *HRouter) Init(confpath string) error {
	{
		confdir := filepath.Dir(confpath)
		confbase := filepath.Base(confpath)
		nametype := strings.Split(confbase, ".")
		if len(nametype) != 2 {
			return seelog.Warnf("confbase has no suffix type. confbase: [%v]", confbase)
		}
		confname := nametype[0]
		conftype := nametype[1]
		viper.AddConfigPath(confdir)
		viper.SetConfigName(confname)
		viper.SetConfigType(conftype)
		if err := viper.ReadInConfig(); err != nil {
			return seelog.Errorf("viper init failed. err: [%v]", err)
		}
		seelog.Info("viper init success.")
		for key, val := range viper.AllSettings() {
			seelog.Infof("%v: %v", key, val)
		}
	}
	{
		h.markdown = &Markdown{}
		h.markdown.Init(viper.GetStringSlice("markdown.directorys"))
	}

	return nil
}

func (h *HRouter) Run() {
	h.router = gin.Default()

	h.router.GET("/helloworld", func(ctx *gin.Context) {
		ctx.String(http.StatusOK, "hello %v", ctx.Query("name"))
	})
	h.router.GET("/markdown/doclist", func(ctx *gin.Context) {
		ctx.JSON(http.StatusOK, gin.H{
			"error":   "ok",
			"doclist": h.markdown.DocList(),
		})
	})
	h.router.GET("/markdown/document", func(ctx *gin.Context) {
		doc := ctx.Query("doc")
		md, err := h.markdown.Document(doc)
		seelog.Info(md)
		if err != nil {
			ctx.JSON(http.StatusOK, gin.H{
				"error": err.Error(),
			})
		} else {
			ctx.JSON(http.StatusOK, gin.H{
				"error":    "ok",
				"markdown": md,
			})
		}
	})

	h.router.Run(":3001")
}
