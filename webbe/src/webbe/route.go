package webbe

import (
	"gopkg.in/gin-gonic/gin.v1"
	"io"
	"net/http"
	"os"
)

type Route struct {
	address string
	engine  *gin.Engine
}

func (r *Route) Init(address string, mode string, logfile string) error {
	r.address = address
	gin.SetMode(mode)

	// set logfile
	gin.DisableConsoleColor()
	fp, err := os.Create(logfile)
	if err != nil {
		return err
	}
	if mode == "debug" {
		gin.DefaultWriter = io.MultiWriter(fp, os.Stdout)
	} else {
		gin.DefaultWriter = io.MultiWriter(fp)
	}
	r.engine = gin.Default()

	r.engine.GET("/test", func(context *gin.Context) {
		context.String(http.StatusOK, "test ok")
	})

	return nil
}

func (r *Route) AddHander(relativePath string, handlerFunc gin.HandlerFunc) {
	r.engine.GET(relativePath, handlerFunc)
}

func (r *Route) Run() error {
	return r.engine.Run(r.address)
}
