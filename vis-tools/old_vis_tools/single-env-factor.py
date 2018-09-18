#! /usr/bin/env python

import argparse
import os

from src import single_map

def parse_args():
    parser = argparse.ArgumentParser(description='Plot a given Env Factor on the board.')
    parser.add_argument('env_factor_file_path', metavar='ef_path', type=str, nargs=1,
                        help='Path to the Environmental Factor .csv file.')
    args = parser.parse_args()
    return args.env_factor_file_path[0]

def main():
    rel_path = parse_args()
    abs_path = os.path.abspath(rel_path)

    single_map.plot_single_map(abs_path)


if __name__ == '__main__':
    main()
