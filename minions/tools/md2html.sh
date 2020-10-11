#!/usr/bin/env bash

markdown2 -x fenced-code-blocks,tables,code-friendly $1 > $1.div

if [[ $2 != "" ]]; then
    html_maker.py --style $2 --div $1.div
else
    html_maker.py --div $1.div
fi

rm $1.div
