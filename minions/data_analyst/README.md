# data_analyst

做这写工具的直接原因是一次在做性能测试的时候，总要从日志中去抓取一些性能数据然后来统计性能结果，因为整个分析的过程大体都相同，所以想做得更加自动化一些

整个分析过程大概分为：
    1. 下载日志文件
    2. 格式化日志文件，只留下关心的字段，并且字段之间用\t来分割
    3. 日志分析，包括过滤不要的行，统计关心的行的信息，比如平均数，分位数等
    4. 将分析的结果制作表格，并以邮件的形式发送给自己

下载日志文件download.sh，用wget比较方便，由于日志可能来自于多台机器，但是在机器上的路径相同，所以对wget封装了一下，来满足这种需求

获取日志文件中感兴趣的字段format_log.py，grep比较强大，但是其局限在于不能一次获取多个字段，并且格式化的输出，这里用python实现了这样的功能，传入一个python的正则表达式，括号括起来的字段将被输出到结果中

日志过滤select.py，grep可以过滤一些行，但是对于一些条件没有办法满足，awk也可以完成类似的功能也比较复杂，这里用select.py实现了一个类似于数据库的操作格式化的数据

日志分析analyst.py，由于python的加法没有精度的限制，因此可以得到较为准确的分位数，平均数结果

## download.sh

日志下载工具

    $ sh download.sh \
        -m "host1 host2" \
        -p "/var/ftp/dir" \
        -f "file.log" \
        -o "data"

## format_log.py

格式日志工具

    $ python format_log.py \
        --input data.log \
        --regex "key0:(\w) key1:(\d+) key2:(\d+)"

## select.py

数据文件处理工具

    $ python create_test_data.py | sort -k1 | python select.py \
        --table "name, value1, value2, value3" \
        --query "SELECT name, max(value2), sum(value3) GROUP BY name WHERE value1 > 90"

    $ python create_test_data.py | sort -k1 | python select.py \
        --query "SELECT 0, max(2), sum(3) group by 1 where 1 > 90"

## analyst.py

数据文件分析工具

    $ python analyst.py \
        --fields 'max_0(key1), min, avg, 0.8_1(eighty_1), 0.9' \
        --index 2 \
        --input in.dt \
        --output out.tb

## table_maker.py && html_maker.py

将分析的结果输出到html文件

    $ python table_maker.py \
        --fields "max, min, avg, 0.8" \
        --datas "aaa.tb, bbb.tb" \
        --output "table.div"

    $ python html_maker.py \
        --style "style.css" \
        --div "table.div" \
        --output "result.html"

## usage_demo.sh

使用方法的一个例子

    $ sh usage_demom.sh
