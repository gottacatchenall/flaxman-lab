#! /usr/bin/env python

import argparse
import os
import copy
import numpy as np
from src import env_factor_map
from src import plot_board
from src import read_fragmentation_data
from src import population_data

def parse_args():
    parser = argparse.ArgumentParser(description='Plot population in each patch over time on the board.')
    parser.add_argument('run_dir_path', metavar='ef_path', type=str, nargs='?',
                        help='Path to the run directory.')
    args = parser.parse_args()
    if (not args):
        return False
    return args.run_dir_path

def main():
    rel_path = parse_args()

    if (not rel_path):
        rel_path = "./"
    envFactors_path = os.path.abspath(rel_path + "envFactors/")
    fragmentation_data_path = os.path.abspath(rel_path + "fragment/fragment_data.csv")
    generations_path = os.path.abspath(rel_path + "generations/")




    color_map = env_factor_map.env_factor_map(envFactors_path)
    pop_data = population_data.population_data(generations_path)
    frag_data = read_fragmentation_data.read_fragmentation_data(fragmentation_data_path)

    n_gen = len(frag_data)
    anim_map = [np.zeros((len(color_map), len(color_map))) for x in range(n_gen)]
    anim_map[0] = color_map
    min_val = np.amin(color_map)

    for i in range(1, n_gen):
        x = int(frag_data[i][1])
        y = int(frag_data[i][2])
        new_map = copy.deepcopy(anim_map[i-1])
        if (x != -1 and y != -1):
            new_map[x][y] = min_val
        anim_map[i] = new_map

    figure, ax = plot_board.setup(len(color_map))
    plot_board.show_w_indivs(figure, ax, anim_map, pop_data, ani=True)


if __name__ == '__main__':
    main()
