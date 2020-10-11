#!/usr/bin/env bash

WORK_ROOT=$(pwd)
THIRD_SRC="${WORK_ROOT}/third_src"
THIRD_LIB="${WORK_ROOT}/third_lib"

if [[ $(uname -s) == "Darwin" ]]; then
    LIBTOOL=glibtool
    LIBTOOLIZE=glibtoolize
fi

mkdir -p ${THIRD_SRC} ${THIRD_LIB}

function warn() {
    echo "\033[31m$1\033[0m"
}

function info() {
    echo "\033[32m$1\033[0m"
}

function install_protobuf {
    libname="protobuf"
    version="v3.5.0"
    cd ${THIRD_SRC} && [[ -e ${libname} ]] || git clone -b ${version} https://github.com/google/${libname}
    [[ -e ${THIRD_LIB}/${libname} ]] && info "${libname} exists" && return 0
    cd ${THIRD_SRC}/${libname} &&
    sh autogen.sh && ./configure --prefix=${THIRD_LIB}/${libname} && make -j8 && make install &&
    info "install protoc success" && return 0
    warn "install protoc fail" && return 255
}

function install_grpc {
    # https://github.com/grpc/grpc/blob/master/INSTALL.md
    export CPLUS_INCLUDE_PATH=${CPLUS_INCLUDE_PATH}:${THIRD_LIB}/protobuf/include
    export LD_LIBRARY_PATH=${THIRD_LIB}/protobuf/lib:${LD_LIBRARY_PATH}
    export LIBRARY_PATH=${THIRD_LIB}/protobuf/lib:${LIBRARY_PATH}
    libname="grpc"
    version="v1.8.x"
    cd ${THIRD_SRC} && [[ -e ${libname} ]] || git clone -b ${version} https://github.com/grpc/{libname} &&
    [[ -e ${THIRD_LIB}/${libname} ]] && info "${libname} exists" && return 0
    cd ${THIRD_SRC}/${libname} && git submodule update --init && make run_dep_checks && make -j8
}

function dependency() {
    if [[ $(uname -s) == "Darwin" ]]; then
        brew install grpc protobuf log4cplus libconfig
    else
        install_protobuf
        install_grpc
    fi
}

function codegen() {
    mkdir -p proto_out/
    protoc -I proto --grpc_out=proto_out --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` proto/greeter.proto
    protoc -I proto --cpp_out=proto_out proto/greeter.proto
}

function usage() {
    info "usage: "
    info "  sh everything.sh <dependency | unit | stat | build | deploy>"
    info "  dependency  安装依赖"
    info "  unit        单元测试[module]"
    info "  stat        统计"
    info "  build       编译[offline | prerelease | release]"
}

function main() {
    case "$1" in
        "dependency") dependency;;
        "codegen") codegen;;
        "unit") unit "$2";;
        "stat") mstat "$2";;
        "build") build "$2";;
        *) usage;;
    esac
}

main "$@"

