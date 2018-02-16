#! /usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np

GRID_SIZE = 64
NUM_OF_HOTSPOTS = 16

class Hotspot():
    def __init__(self, x, y):
        self.x = x
        self.y = y


class Board():
    def __init__(self):
        self.size = GRID_SIZE
        self.num_of_hotspots = NUM_OF_HOTSPOTS
        self.setup_plot()

    # ====================================
    # Plotting
    # ====================================

    def setup_plot(self):
        self.figure, self.ax = plt.subplots(figsize=(7,7))
        self.ax.grid(linestyle='-', linewidth=.5)
        self.ax.set_xticks(np.arange(0, GRID_SIZE, 1))
        self.ax.set_yticks(np.arange(0, GRID_SIZE, 1))
        self.ax.set_xlim([0, GRID_SIZE])
        self.ax.set_ylim([0, GRID_SIZE])
        plt.tick_params(axis='both', which='both', left='off', labelleft='off', bottom='off', labelbottom='off')

    def show_board(self):
        plt.show()


    # ====================================
    # Hotspots
    # ====================================

    def pick_hotspot_points(self):
        x = np.floor((self.size) * np.random.rand(1, self.num_of_hotspots)) + 0.5
        y = np.floor((self.size) * np.random.rand(1, self.num_of_hotspots)) + 0.5
        return (x,y)


    def init_hotspots(self):

        x,y = self.pick_hotspot_points()
        self.ax.scatter(x, y)
        for i in range(0, len(x)):
            hotspot = Hotspot(x[i],y[i])

def main():
    board = Board()
    board.init_hotspots()
    board.show_board()


if __name__ == '__main__':
    main()
