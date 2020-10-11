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
    output="htool"
    mkdir -p ${output} &&
    find . -type f -maxdepth 1 -perm 755 -exec cp {} htool \; &&
    cp everything.sh htool &&
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
    output="htool"

    if [[ ! -z $1 ]]; then
        host=$1
    fi
    if [[ ! -z $2 ]]; then
        dest=$2
    fi
    if [[ ! -z $3 ]]; then
        user=$3
    fi

    ansible ${host} -m copy -a "src=${output} dest=${dest} owner=${user} mode=755" &&
    ansible ${host} -m cron -a "
        user='hatlonely'
        name='ip_report'
        minute='*/15'
        job='source ~/.zshrc && hclient set mini \$(hip)'
    " &&
    ansible ${host} -m cron -a "
        user='hatlonely'
        name='code_report'
        minute='0'
        hour='4'
        job='source ~/.zshrc && mkdir -p ~/hatlonely/code && cd ~/hatlonely/code && htechstat_report 1.days.ago >> htechstat_report.log'
    " &&

    info "deploy ${user}@${host}:${dest}/${output} success" ||
    warn "deploy ${user}@${host}:${dest}/${output} failed"
}

function install() {
    module="python3"
    host="mini"
    dest="~/local"
    user="hatlonely"

    if [[ ! -z $1 ]]; then
        module=$1
    fi
    if [[ ! -z $2 ]]; then
        host=$2
    fi
    if [[ ! -z $3 ]]; then
        dest=$3
    fi
    if [[ ! -z $4 ]]; then
        user=$4
    fi

    if [[ ! -e $(pwd)/output/${module}.tar.gz ]]; then
        ./hinstall ${module} $(pwd)/output/${module}
        (cd $(pwd)/output/ && tar -czvf ${module}.tar.gz ${module})
    fi
    ansible ${host} -m copy -a "src=$(pwd)/output/${module}.tar.gz dest=${dest} owner=${user} mode=755" &&
    ansible ${host} -a "cd ${dest} && tar -xzvf ${dest}/${module}.tar.gz" -s &&
    info "deploy ${user}@${host}:${dest}/${module} success" ||
    warn "deploy ${user}@${host}:${dest}/${module} fail"
}

function usage() {
    echo "sh everything.sh <cmd> [args]"
    echo "example:"
    echo "  sh everything.sh pack"
    echo "  sh everything.sh deploy <host> <dest> <user>"
    echo "  sh everything.sh version"
    echo "  sh everything.sh install <module> <host> <dest> <user>"
}

function main() {
    case $1 in
        "pack") pack;;
        "deploy") deploy;;
        "version") version;;
        "install") install "$2" "$3" "$4" "$5";;
        *) usage;;
    esac
}

main "$@"
