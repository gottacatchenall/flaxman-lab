#! /usr/bin/env python

import argparse, os
import numpy as np
from plotting import setup
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
#from src import single_map

def parse_args():
    parser = argparse.ArgumentParser(description='Plot a given Env Factor on the board.')
    parser.add_argument('env_factor_file_path', metavar='ef_path', type=str, nargs=1,
                        help='Path to the Environmental Factor .csv file.')
    args = parser.parse_args()
    return args.env_factor_file_path[0]

def read_single_map(abs_path):
    m = np.loadtxt(open(abs_path, "rb"), delimiter=",")
    x = [[i for i in range(0, len(m))] for j in range(0, len(m))]
    y =[[j for i in range(0, len(m))] for j in range(0, len(m))]

    # 3d plot

    #fig = plt.figure()
    #ax = fig.gca(projection='3d')
    #ax.plot_surface(x,y,m, cmap="gist_earth")
    #plt.show()


    figure, ax = setup(len(m))
    show(figure, ax, m)


def show(figure, ax, m):
    im = plt.imshow(m, interpolation='none', aspect='equal', cmap='binary')
    plt.colorbar()
    plt.show()


def main():
    rel_path = parse_args()
    abs_path = os.path.abspath(rel_path)
    read_single_map(abs_path)


if __name__ == '__main__':
    main()
