HATLONELY_GIT_WORKSPACE=$HOME/hatlonely/git_workspace
HATLONELY_LOCAL=$HOME/local

function path_append() {
    if [[ -e ${HATLONELY_GIT_WORKSPACE}/$1 ]]; then
        PATH=${HATLONELY_GIT_WORKSPACE}/$1:$PATH
    fi
}

PATH=${HATLONELY_LOCAL}/bin:$PATH
PATH=$HOME/local/bin:$PATH
path_append minions/data_analyst
path_append minions/rand
path_append minions/tplmake
path_append minions/install
path_append minions/tools
path_append minions/md2html
path_append pyfiglet/tools
path_append python-markdown2/bin
path_append marked/bin
