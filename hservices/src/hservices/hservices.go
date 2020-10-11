package hservices

import (
	"fmt"
	"github.com/cihub/seelog"
	"github.com/hatlonely/hgo/src/hutil"
	"github.com/spf13/viper"
)

var route *Route
var woklog seelog.LoggerInterface
var acclog seelog.LoggerInterface
var satlog seelog.LoggerInterface

func Init(confpath string) error {
	confdir, confbase, conftype, err := hutil.ParseConfigPath(confpath)
	if err != nil {
		return seelog.Errorf("parse config path failed. %v", err)
	}

	{
		var err error
		if woklog, err = seelog.LoggerFromConfigAsFile(fmt.Sprintf("%v/hservices_woklog.xml", confdir)); err != nil {
			return seelog.Errorf("woklog init failed. err: [%v]", err)
		}
		if acclog, err = seelog.LoggerFromConfigAsFile(fmt.Sprintf("%v/hservices_acclog.xml", confdir)); err != nil {
			return seelog.Errorf("acclog init failed. err: [%v]", err)
		}
		if satlog, err = seelog.LoggerFromConfigAsFile(fmt.Sprintf("%v/hservices_satlog.xml", confdir)); err != nil {
			return seelog.Errorf("satlog init failed. err: [%v]", err)
		}
		seelog.ReplaceLogger(woklog)
	}

	config := viper.New()
	{
		config.AddConfigPath(confdir)
		config.SetConfigName(confbase)
		config.SetConfigType(conftype)
		if err := config.ReadInConfig(); err != nil {
			return seelog.Errorf("viper init failed. err: [%v]", err)
		}
		seelog.Info("viper init success.")
		for key, val := range config.AllSettings() {
			seelog.Infof("%v: %v", key, val)
		}
	}

	if err := route.Init(fmt.Sprintf(":%v", config.GetInt("port"))); err != nil {
		return seelog.Errorf("route init failed.")
	}

	return nil
}

func Run() error {
	return route.Run()
}
