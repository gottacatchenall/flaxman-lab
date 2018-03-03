#! /usr/bin/env python

import argparse
import csv
import os
import numpy as np

from plot_board import setup
from plot_board import show

def parse_args():
    parser = argparse.ArgumentParser(description='Plot a given Env Factor on the board.')
    parser.add_argument('env_factor_file_path', metavar='ef_path', type=str, nargs=1,
                        help='Path to the Environmental Factor .csv file.')
    args = parser.parse_args()
    return args.env_factor_file_path[0]

def main():
    rel_path = parse_args()
    abs_path = os.path.abspath(rel_path)
    print abs_path
    with open(abs_path, 'rU') as p:
        tmp = [list(map(int,rec)) for rec in csv.reader(p, delimiter=',')]

    board_size = len(tmp)
    m = np.zeros((board_size, board_size))

    for i in range(len(tmp)):
        for j in range(len(tmp[i])):
            m[i,j] = tmp[i][j]

    #print m

    figure, ax = setup(len(m))
    show(figure, ax, m)



if __name__ == '__main__':
    main()
