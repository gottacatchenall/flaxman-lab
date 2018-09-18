
from plot_board import setup, show
import numpy as np
import csv

def plot_single_map(abs_path):
    with open(abs_path, 'rU') as p:
        tmp = [list(map(float,rec)) for rec in csv.reader(p, delimiter=',')]

    board_size = len(tmp)
    m = np.zeros((board_size, board_size))

    for i in range(len(tmp)):
        for j in range(len(tmp[i])):
            m[i,j] = tmp[i][j]

    #print m

    figure, ax = setup(len(m))
    show(figure, ax, m)
