#!/usr/bin/env bash

readonly GIT_WORKSPACE=$HOME/hatlonely/git_workspace
readonly APPSOURCE=$HOME/appsource
readonly LOCAL=$HOME/local

error() {
    echo "[$(date +'%Y-%m-%d %H:%M:%S')]: $@" >&2
}

notice() {
    echo "[$(date +'%Y-%m-%d %H:%M:%S')]: $@" >&1
}

# 从github上克隆项目
# Globals:
#   GIT_WORKSPACE     安装目录
# Arguments:
#   $1 username     github上的用户名
#   $2 repository   github上的repository
# Returns:
#   None
clone_repository() {
    cd ${GIT_WORKSPACE}
    if [[ ! -e $2 ]]; then
        notice "git clone git@github.com:$1/$2.git"
        git clone git@github.com:$1/$2.git
        notice "## clone $2 success!!!"
    else
        notice "## $2 is exist. skip..."
    fi
    notice "==========================="
}

# 这个脚本的用法
hget_usage() {
    notice "`basename $0` <software | ls> <install | usage>"
    notice "`basename $0` ls"
    notice "`basename $0` list"
    notice "`basename $0` figlet install"
    notice "`basename $0` marked usage"
}

# 列出可用的安装
hget_list() {
    ls `dirname $0`/apps
}

mkdir -p ${GIT_WORKSPACE}
mkdir -p ${APPSOURCE}
mkdir -p ${LOCAL}

if [[ $1 == "list" || $1 == "ls" ]]; then
    hget_list
    exit 0
elif [[ $1 == "help" || $1 == "-h" ]]; then
    hget_usage
    exit 0
elif [[ $1 != "" ]]; then
    source `dirname $0`/apps/$1
else
    hget_usage
    exit 1
fi

if [[ $2 == "install" ]]; then
    install
elif [[ $2 == "usage" ]]; then
    usage
else
    hget_usage
fi
