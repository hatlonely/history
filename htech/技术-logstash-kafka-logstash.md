技术-logstash-kafka-logstash
===========================

简介
---

logstash用于日志的收集和传输,类似于linux的管道,支持多种输入和输出,包括最常见的输入:标准输入,文件,kafka,常见的输出:标准输出,文件输出,kafka,kinesis,elasticsearch,支持数据的过滤和处理
kafka用于日志的存储和分发  

kafka版本: <http://mirrors.tuna.tsinghua.edu.cn/apache/kafka/0.10.2.0/kafka_2.11-0.10.2.0.tgz>  
logstash版本: <https://artifacts.elastic.co/downloads/logstash/logstash-5.4.2.tar.gz>  

服务的部署和启动
--------------

### mac os

```
brew install kafka
brew install logstash
brew services start kafka
```

logstash => kafka
-----------------

```
logstash -e "
    input {
        stdin {
        }
    }

    output {
        kafka {
            topic_id => 'hatlonely-topic-log-txt-0-test'
            codec => 'plain'
            sasl_mechanism => PLAIN
            security_protocol => SASL_PLAINTEXT
            jaas_path => 'conf/kafka_client_jaas.conf'
        }
    }
"
```

kafka => logstash
-----------------

```
logstash -e "
    input {
        kafka {
            topics => [
                'hatlonely-topic-log-txt-0-test',
                'hatlonely-topic-log-txt-1-test',
            ]
            group_id => 'hatlonely'
            codec => 'plain'
            consumer_threads => 10
            decorate_events => true
            sasl_mechanism => PLAIN
            security_protocol => SASL_PLAINTEXT
            jaas_path => 'conf/kafka_client_jaas.conf'
        }
    }

    output {
        stdout {
            codec => json_lines
        }
    }
"
```

参考链接
-------

* [logstash官方文档]<https://www.elastic.co/guide/en/logstash/current/index.html>
* [logstash => kafka]<https://www.elastic.co/guide/en/logstash/current/plugins-outputs-kafka.html>
* [kafka => logstash]<https://www.elastic.co/guide/en/logstash/current/plugins-inputs-kafka.html>
* [logstash-output-kafka在kafka挂掉之后丢数据]<https://github.com/logstash-plugins/logstash-output-kafka/issues/48>

