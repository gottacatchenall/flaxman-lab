#! /usr/bin/env python

import argparse
import os

from src import single_map

def parse_args():
    parser = argparse.ArgumentParser(description='Plot the fragmentation map on the board.')
    parser.add_argument('frag_map_file_path', metavar='ef_path', type=str, nargs='?',
                        help='Path to the fragmentation map .csv file.')
    args = parser.parse_args()
    if (not args.frag_map_file_path):
        return False
    return args.frag_map_file_path[0]

def main():
    rel_path = parse_args()
    if (not rel_path):
        rel_path = "./fragment/fragment_map.csv"
    abs_path = os.path.abspath(rel_path)

    single_map.plot_single_map(abs_path)


if __name__ == '__main__':
    main()
