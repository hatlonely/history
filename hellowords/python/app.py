#coding: utf-8

import random
from flask import Flask, jsonify, render_template
app = Flask(__name__)

words = []

def loadWords(wordsTxt):
    for line in open(wordsTxt):
        words.append(line.strip().split('\t')[1])

@app.route('/')
def index():
    return words[random.randint(0, len(words) - 1)]

if __name__ == '__main__':
    loadWords('../data/one.txt')
    app.run()
