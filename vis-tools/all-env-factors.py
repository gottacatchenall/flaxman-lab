#! /usr/bin/env python

import argparse
import csv
import os
import numpy as np
import glob, os

from src import env_factor_map

from src import plot_board

def parse_args():
    parser = argparse.ArgumentParser(description='Plot all Env Factors on the board.')
    parser.add_argument('env_factor_dir_path', metavar='ef_path', type=str, nargs='?',
                        help='Path to the Environmental Factor directory.')
    args = parser.parse_args()
    if (not args):
        return False
    return args.env_factor_dir_path

def main():
    rel_path = parse_args()
    if (not rel_path):
        rel_path = "envFactors/" 
    color_map = env_factor_map.env_factor_map(rel_path)
    figure, ax = plot_board.setup(len(color_map))
    plot_board.show(figure, ax, color_map, ani=False)


if __name__ == '__main__':
    main()
