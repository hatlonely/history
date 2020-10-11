#!/usr/bin/env bash

function warn() {
    echo "[31m$1[0m"
}

function info() {
    echo "[32m$1[0m"
}

function version() {
    cat version
}

function pack() {
    output="output/mstat"
    mkdir -p ${output} &&
    cp -r code/* ${output} &&
    cp everything.sh ${output} &&
    echo "version:  $(git describe --tags) [git describe --tags]" > ${output}/version &&
    echo "hashcode: $(git rev-parse HEAD) [git rev-parse HEAD]" >> ${output}/version &&
    echo "datetime: $(date '+%Y-%m-%d %H:%M:%S') [date]" >> ${output}/version &&
    echo "hostname: $(hostname) [hostname]" >> ${output}/version &&
    info "pack success" ||
    warn "pack fail"
}

function deploy() {
    host="mini"
    dest="~/local"
    user="hatlonely"
    output="mstat"

    if [[ ! -z $1 ]]; then
        host=$1
    fi
    if [[ ! -z $2 ]]; then
        dest=$2
    fi
    if [[ ! -z $3 ]]; then
        user=$3
    fi

    ansible ${host} -m copy -a "src=output/${output} dest=${dest} owner=${user} mode=755" &&
    info "deploy ${user}@${host}:${dest}/${output} success" ||
    warn "deploy ${user}@${host}:${dest}/${output} failed"

    # 每天运行
    ansible ${host} -m cron -a "
        user='${user}'
        name='mstat_mcode_main'
        minute='5'
        hour='3'
        job='cd /usr/local/mstat && mkdir -p log && ./main 1.days.ago >> log/mstat.info.\$(date +\\%Y\\%m\\%d)'
    "
}

function usage() {
    echo "sh everything.sh <cmd> [args]"
    echo "example:"
    echo "  sh everything.sh pack"
    echo "  sh everything.sh deploy <host> <dest> <user>"
}

function main() {
    case $1 in
        "pack") pack;;
        "deploy") deploy "$2" "$3" "$4";;
        "version") version;;
        *) usage;;
    esac
}

main "$@"

