#!/bin/bash

# install git
yum install -y git

# install go
yum install -y go

# install python3
yum install -y python36 python36-setuptools python36-pip
pip3 install requests
pip3 install flask
pip3 install redis
pip3 install pymongo
pip3 install behave
pip3 install pyhamcrest
pip3 install pymysql

# install zsh
yum install -y zsh
sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)" <<EOF
Y
EOF
chsh -s /bin/zsh root
