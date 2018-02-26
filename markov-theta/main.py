#! /usr/bin/env python

from matplotlib import pyplot as plt
import numpy as np
import copy

GRID_SIZE = 64

def setup():
    figure = plt.figure(figsize=(7,7))
    ax = plt.gca()
    ax.grid(linestyle='-', linewidth=.5)

    # Major ticks
    #ax.set_xticks(np.arange(0, GRID_SIZE, 1));
    #ax.set_yticks(np.arange(0, GRID_SIZE, 1));


    # Minor ticks
    ax.set_xticks(np.arange(-.5, GRID_SIZE, 1));
    ax.set_yticks(np.arange(-.5, GRID_SIZE, 1));

    # Gridlines based on minor ticks
    ax.grid(color='black', linestyle='-', linewidth=.3)
    ax.set_xlim([-.5, GRID_SIZE-.5])
    ax.set_ylim([-.5, GRID_SIZE-.5])
    plt.tick_params(axis='both', which='both', left='off', labelleft='off', bottom='off', labelbottom='off')


def show(m):
    im = plt.imshow(m, interpolation='none', aspect='equal', cmap="gist_earth")
    plt.show()

def add(m0):
        m = copy.deepcopy(m0)
        def count_surroundings(i,j):
            c = 0
            if (m[i+1,j+1] == -1): c += 1
            if (m[i+1,j] == -1): c += 1
            if (m[i+1,j-1] == -1): c += 1
            if (m[i,j-1] == -1): c += 1
            if (m[i,j+1] == -1): c += 1
            if (m[i-1,j+1] == -1): c += 1
            if (m[i-1,j] == -1): c += 1
            if (m[i-1,j-1] == -1): c += 1
            return c

        base_prob = 0.05

        for i in range(1, GRID_SIZE-1):
            for j in range(1, GRID_SIZE-1):
                c = count_surroundings(i,j)
                if (np.random.random() < c*base_prob):
                    m[i,j] = -1
                if (c > 5):
                    m[i,j] = -1

        return m

def main():
    m = np.zeros((GRID_SIZE, GRID_SIZE))

    x,y = np.random.randint(0, GRID_SIZE), np.random.randint(0, GRID_SIZE)
    m[x,y] = -1

    for i in range(100):
        m = add(m)

    setup()
    show(m)










if __name__ == '__main__':
  main()
