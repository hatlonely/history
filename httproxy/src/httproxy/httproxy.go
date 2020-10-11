package httproxy

import (
	"github.com/cihub/seelog"
	"github.com/hatlonely/hgo/src/hstore"
	"github.com/hatlonely/hgo/src/hutil"
	"github.com/spf13/viper"
)

var woklog seelog.LoggerInterface
var acclog seelog.LoggerInterface
var satlog seelog.LoggerInterface
var route *Route
var redis *hstore.HRedis
var proxy *Proxy

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
		redis = &hstore.HRedis{}
		if err := redis.Init(
			config.GetString("redis.address"), config.GetInt("redis.maxidle"),
			config.GetDuration("redis.timeout"), config.GetInt("redis.retryTimes"),
		); err != nil {
			return seelog.Errorf("redis init failed. err: [%v]", err)
		}
	}

	{
		proxy = &Proxy{}
		if err := proxy.Init(config.GetStringMapString("proxy"), redis, route); err != nil {
			return seelog.Errorf("proxy init failed. err: [%v]", err)
		}
	}

	return nil
}

func Run() {
	go route.Run()
}
