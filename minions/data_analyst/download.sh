#!/usr/bin/env bash
###
# 从服务器上下载数据脚本，内部封装wget
# 支持从多个机器的相同路径下载相同文件
# 
# Author: hatlonely(hatlonely@gmail.com)
# Date: 2014-12-05
###

# 颜色相关
GREEN="\033[32m"    # 成功
RED="\033[31m"      # 警告
YELLOW="\033[33m"   # 注意
OFF_COLOR="\033[0m"

function usage() {
    echo -e "${GREEN}usage:${OFF_COLOR}"
    echo "  ${0##*/} [-h] <-m machine_list> <-p path> <-f file> <-o output_dir> [-d date] [-r limit_rate]"
    echo "  [-h]                帮助"
    echo "  <-m machine_list>   机器列表"
    echo "  <-p path>           日志文件路径"
    echo "  <-f file>           日志文件名"
    echo "  <-o output_dir>     输入文件路径"
    echo "  [-s suffix]         日志文件后缀，一般日期的后缀格式yyyymmdd"
    echo "  [-r limit_rate]     限速, 默认30M"
    echo -e "${GREEN}example:${OFF_COLOR}"
    echo "  sh ${0##*/} -m \"host1 host2\" -p \"/var/ftp/dir\" -f \"file.log\" -o \"data\""
}

function check_parameter() {
    if [ -z $1 ]; then
        echo -e "${RED}[FATAL]${OFF_COLOR} miss parameter"
        usage
        exit 0
    fi
}

while getopts "hm:p:f:s:o:r:" options; do
    case ${options} in
        h) HELP="TRUE";;
        m) MACHINE=${OPTARG};;
        p) DOWNLOAD_PATH=${OPTARG};;
        f) DOWNLOAD_FILE=${OPTARG};;
        s) DATE=${OPTARG};;
        o) OUTPUT_PATH=${OPTARG};;
        r) LIMIT_RATE=${OPTARG};;
        ?) usage; exit -1;;
    esac
done

if [[ ${HELP} == "TRUE" ]]; then
    usage
    exit 0
fi

if [[ ! -z ${DATE} ]]; then
    DOWNLOAD_FILE=${DOWNLOAD_FILE}.${DATE}
fi

if [[ -z ${OUTPUT_PATH} ]]; then
    OUTPUT_PATH="."
fi

if [[ -z ${LIMIT_RATE} ]]; then
    LIMIT_RATE="30M"
fi

check_parameter ${MACHINE}
check_parameter ${DOWNLOAD_PATH}
check_parameter ${DOWNLOAD_FILE}

for machine in ${MACHINE}; do
    if [ -e ${OUTPUT_PATH}/${DOWNLOAD_FILE}.${machine} ]; then
        echo "${OUTPUT_PATH}/${DOWNLOAD_FILE}.${machine}已经存在，跳过..."
    else
        echo "wget --limit-rate=${LIMIT_RATE} -q ftp://${machine}:${DOWNLOAD_PATH}/${DOWNLOAD_FILE} -O ${OUTPUT_PATH}/${DOWNLOAD_FILE}.${machine}"
        wget --limit-rate=${LIMIT_RATE} -q ftp://${machine}:${DOWNLOAD_PATH}/${DOWNLOAD_FILE} -O ${OUTPUT_PATH}/${DOWNLOAD_FILE}.${machine}
    fi
done
