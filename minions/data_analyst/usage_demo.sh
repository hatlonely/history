#!/usr/bin/env bash

TMP=tmp

mkdir -p ${TMP}
 
# step1 下载日志文件
# sh download.sh -m "127.0.0.1" -p `pwd` -f "test.log" -o "data"
python create_test_data.py > ${TMP}/test.log

# step2 从日志中提取需要的字段，格式化到一个新的文件中
python format_log.py \
    --input "${TMP}/test.log" \
    --regex "OnePiece: (.*?) funny\[(\d+)\], lovely\[(\d+)\], damage\[(\d+)\]" \
    --output "$TMP/test.dt"

# step3 筛选出需要的列，select.py要求输入的文件已经按照group by中的字段排序
sort -k1 $TMP/test.dt > $TMP/test.dt.sort  # 如果不用group by，此处不需要排序
python select.py \
    --table "role, funny, lovely, demage" \
    --query "select role, count, sum(funny), sum(lovely), sum(demage) GROUP BY role WHERE funny > 50" \
    --input "${TMP}/test.dt.sort" \
    --output "$TMP/test.select.dt"

# step4 计算最大值，最小值，平均数，分位数
python analyst.py \
    --fields "max, min, avg, 0.8, 0.9" \
    --index 1 \
    --input "${TMP}/test.select.dt" \
    --output "${TMP}/count.tb"

python analyst.py \
    --fields "max, min, avg, 0.8, 0.9" \
    --index 2 --input "${TMP}/test.select.dt" \
    --output "${TMP}/funny.tb"

python analyst.py \
    --fields "max, min, avg, 0.8, 0.9" \
    --index 3 \
    --input "${TMP}/test.select.dt" \
    --output "${TMP}/lovely.tb"

python analyst.py \
    --fields "max, min, avg, 0.8, 0.9" \
    --index 4 \
    --input "${TMP}/test.select.dt" \
    --output "${TMP}/demage.tb"

# step5 将数据做成html表格
python table_maker.py \
    --fields "max, min, avg, 0.8, 0.9" \
    --datas "${TMP}/count.tb(count), ${TMP}/funny.tb(funny), ${TMP}/lovely.tb(lovely), ${TMP}/demage.tb(demage)" \
    --title "onepiece" \
    --output "${TMP}/onepiece.div"

python html_maker.py \
    --style "style.css" \
    --div "${TMP}/onepiece.div" \
    --output "onepiece.html"

# step6 以邮件的形式发送
cat ${TMP}/onepiece.html | mail \
    -s "$(echo -e "atom daily report\nContent-Type: text/html;charset=utf-8")" \
    "hatlonely@gmail.com"

rm -rf ${TMP}
