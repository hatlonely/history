package hservices

import "gopkg.in/gin-gonic/gin.v1"

type Route struct {
	address string
	engine  *gin.Engine
}

func (r *Route) Init(address string) error {
	r.address = address
	r.engine = gin.Default()

	return nil
}

func (r *Route) GET(path string, handler func(*gin.Context)) {
	r.engine.GET(path, handler)
}

func (r *Route) Run() error {
	return r.engine.Run(r.address)
}
