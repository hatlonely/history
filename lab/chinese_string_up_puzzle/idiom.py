#!/usr/bin/env python3

import argparse
import random

idiom_map = {}


def init():
    for word in open("idiom.txt"):
        if word[0] not in idiom_map:
            idiom_map[word[0]] = []
        idiom_map[word[0]].append(word[:-1])


def next(w):
    wordss = []
    wss = idiom_map[w[-1]]
    for w in wss:
        words = [w]
        for _ in range(11):
            ch = w[-1]
            if ch not in idiom_map:
                break
            ws = idiom_map[ch]
            w = ws[random.randint(0, len(ws) - 1)]
            words.append(w)
        wordss.append(words)
    return wordss


def main():
    init()
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description="""Example:
            python3 idiom.py -w "宾客如云"
        """
    )
    parser.add_argument("-w", "--word", help="word", default="长")
    args = parser.parse_args()
    for ws in next(args.word):
        print(" ".join(ws))


if __name__ == "__main__":
    main()
