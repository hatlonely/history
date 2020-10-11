#!/usr/bin/env python3

import os
import csv
import sys
import numpy as np
import math
from itertools import groupby


def travel(directory):
    for name in os.listdir(directory):
        filename = os.path.join(directory, name)
        if not os.path.isfile(filename):
            continue
        yield filename


def find_inflection_point(filename):
    with open(filename, 'r', encoding="iso-8859-1") as csvfile:
        reader = csv.reader(csvfile, delimiter=';')
        rows = []
        for row in reader:
            if len(row) == 11 and row[0] == '0':
                rows.append(row)
                break
        for row in reader:
            if len(row) != 11:
                break
            rows.append(row)
        rows = [[int(row[0]), float(row[7]), float(row[8])]
                for row in rows]
        row_group = []
        max_x = max([v[1] for v in rows])
        min_x = min([v[1] for v in rows])
        max_y = max([v[2] for v in rows])
        min_y = min([v[2] for v in rows])
        f = (max_x - min_x) / 1000.0
        for _, vals in groupby(rows, lambda v: int(v[1] / f) * f):
            vals = [v for v in vals]
            v = [np.average([v[0] for v in vals]),
                 np.average([v[1] for v in vals]),
                 np.average([v[2] for v in vals])]
            row_group.append(v)
        rows = row_group

        d = 10
        lastak = None
        lastx = None
        diffak = sys.float_info.min
        v = None
        for i in range(d, len(rows)):
            x = [row[1] for row in rows[i-d:i]]
            y = [row[2] for row in rows[i-d:i]]
            k, b = np.polyfit(x, y, 1)
            if not lastak:
                lastak = math.atan(k)
                lastx = np.average(x)
                continue
            currak = math.atan(k)
            currx = np.average(x)
            curry = np.average(y)
            if diffak < (currak - lastak) / (currx - lastx) and (max_y - curry) / (max_y - min_y) > 0.3:
                diffak = (currak - lastak) / (currx - lastx)
                v = [i, currx, curry]
            lastak = currak
        return v


def main():
    out = open('inflection_point.txt', 'w')
    for filename in travel('data2'):
        row = find_inflection_point(filename)
        out.write('{}\t{}\t{}\t{}\n'.format(filename, row[0], row[1], row[2]))
        print('{}\t{}\t{}\t{}'.format(filename, row[0], row[1], row[2]))
    out.close()


if __name__ == '__main__':
    main()
