#!/usr/bin/env bash

INSTALL_DIR=$HOME/hatlonely/git_workspace

mkdir -p ${INSTALL_DIR}

function clone_repository() {
    cd ${INSTALL_DIR}
    if [[ ! -e $2 ]]; then
        git clone git@github.com:$1/$2.git
        echo "## clone $2 success!!!"
    else
        echo "## $2 is exist. skip..."
    fi
    echo ""
}

function clone_hatlonely_repository() {
    clone_repository hatlonely $1
}

clone_hatlonely_repository crystal
clone_hatlonely_repository minions
clone_hatlonely_repository spider
clone_hatlonely_repository helloworld
clone_hatlonely_repository maze
clone_hatlonely_repository notebook

clone_repository isagalaev highlight.js
