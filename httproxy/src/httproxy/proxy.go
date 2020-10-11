package httproxy

import (
	"github.com/hatlonely/hgo/src/hstore"
	"gopkg.in/gin-gonic/gin.v1"
	"net/http"
	"strings"
)

type Proxy struct {
	urlMapping map[string]string
	redis      *hstore.HRedis
	route      *Route
}

func (p *Proxy) Init(urlMapping map[string]string, redis *hstore.HRedis, route *Route) error {
	p.urlMapping = urlMapping
	p.redis = redis
	p.route = route

	for reltivePath := range urlMapping {
		p.route.AddHander(reltivePath, p.Handler)
	}

	return nil
}

func FindPlaceholders(originUrl string) []string {
	placeHolders := []string{}

	for i := range originUrl {
		if originUrl[i] == '{' {
			j := i + 1
			for j < len(originUrl) && originUrl[j] != '}' {
				j++
			}
			if j != len(originUrl) {
				placeHolders = append(placeHolders, originUrl[i+1:j])
			}
		}
	}

	return placeHolders
}

func (p *Proxy) FormatUrl(originUrl string) (string, error) {
	placeholders := FindPlaceholders(originUrl)
	formatUrl := originUrl
	for _, placeholder := range placeholders {
		val, err := p.redis.Get(placeholder)
		if err != nil {
			return "", err
		}
		if val == nil {
			formatUrl = strings.Replace(formatUrl, "{"+placeholder+"}", "", 1)
		} else {
			formatUrl = strings.Replace(formatUrl, "{"+placeholder+"}", val.(string), 1)
		}
	}

	return formatUrl, nil
}

func (p *Proxy) Handler(ctx *gin.Context) {
	reltivePath := ctx.Request.URL.Path
	originalUrl, ok := proxy.urlMapping[reltivePath]
	if !ok {
		ctx.String(http.StatusNotFound, "404 not found")
	}
	formatUrl, err := p.FormatUrl(originalUrl)
	formatUrl += "?" + ctx.Request.URL.RawQuery
	ctx.Header("Access-Control-Allow-Origin", "*")
	if err != nil {
		ctx.String(http.StatusInternalServerError, err.Error())
	}
	ctx.Redirect(http.StatusFound, formatUrl)
}
