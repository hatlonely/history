package webbe

import (
	"github.com/cihub/seelog"
	"github.com/hatlonely/hgo/src/hutil"
	"github.com/spf13/viper"
	"markdown"
	"article_mysql"
)

var woklog seelog.LoggerInterface
var acclog seelog.LoggerInterface
var satlog seelog.LoggerInterface
var route *Route
var md *markdown.Markdown
var mysql *article_mysql.ArticleMysql

func Init(confpath string) error {
	confdir, confbase, conftype, err := hutil.ParseConfigPath(confpath)
	if err != nil {
		return seelog.Errorf("parse config path failed. %v", err)
	}

	config := viper.New()
	{
		config.AddConfigPath(confdir)
		config.SetConfigName(confbase)
		config.SetConfigType(conftype)
		if err := config.ReadInConfig(); err != nil {
			return seelog.Errorf("viper init failed. err: [%v]", err)
		}
	}

	{
		var err error
		if woklog, err = seelog.LoggerFromConfigAsFile(config.GetString("logger.woklog")); err != nil {
			seelog.Errorf("woklog init failed. err: [%v]", err)
		}
		if acclog, err = seelog.LoggerFromConfigAsFile(config.GetString("logger.acclog")); err != nil {
			seelog.Errorf("acclog init failed. err: [%v]", err)
		}
		if satlog, err = seelog.LoggerFromConfigAsFile(config.GetString("logger.satlog")); err != nil {
			seelog.Errorf("satlog init failed. err: [%v]", err)
		}
		seelog.ReplaceLogger(woklog)

		for key, val := range config.AllSettings() {
			seelog.Infof("%v: %v", key, val)
		}
	}

	{
		route = &Route{}
		if err := route.Init(
			config.GetString("route.address"), config.GetString("route.mode"), config.GetString("route.logfile"),
		); err != nil {
			return seelog.Errorf("route init failed. err: [%v]", err)
		}
	}

	{
		mysql = &article_mysql.ArticleMysql{}
		if err := mysql.Init(config.GetString("mysql.uri"),
			config.GetInt("mysql.max_idle_conn"),
			config.GetInt("mysql.max_open_conn")); err != nil {
			return seelog.Errorf("mysql init failed. err: [%v]", err)
		}
	}

	{
		md = &markdown.Markdown{}
		if err := md.Init(config.GetString("markdown.dirname"), mysql); err != nil {
			return seelog.Errorf("markdown init failed. err: [%v]", err)
		}
		route.AddHander("/md", md.DocsHandler)
		route.AddHander("/doclist", md.ListHandler)
	}

	return nil
}

func Run() {
	go route.Run()
}
