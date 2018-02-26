import numpy as np
import heapq
import matplotlib
import scipy.spatial as spatial
import copy
from envfactor import EnvFactor
from plot import setup, show
from matplotlib import pyplot as plt

GRID_SIZE = 64
NUM_OF_HOTSPOTS = 32

np.set_printoptions(threshold=np.nan)

class Board():

    envFactors = []

    def __init__(self):
        self.size = GRID_SIZE
        self.num_of_hotspots = NUM_OF_HOTSPOTS
        self.setup_plot()

    # ====================================
    # Plotting
    # ====================================

    def setup_plot(self):
        self.figure, self.ax = setup(GRID_SIZE)

    def show_board(self, maps):
        show(self.figure, self.ax, maps)



    # ====================================
    # Hotspots
    # ====================================

    def pick_hotspot_points(self):
        points = np.random.randint(0, GRID_SIZE, size=(self.num_of_hotspots, 2))
        return points


    def init_hotspots(self):

        init_sigma = np.floor(GRID_SIZE / 2) + np.random.normal(0, 4, NUM_OF_HOTSPOTS)

        points = self.pick_hotspot_points()
        x = points[:,0]
        y = points[:,1]

        i = 0
        ind = 0
        while i < 32:
            min_dist = 10000
            min_dist_ind = 0
            for j in range(0, len(x)):
                if (x[j] != -1  and ind != j):
                    d = ((x[ind] - x[j])**2 + (y[ind] - y[j])**2)
                    if (d < min_dist):
                        min_dist = d
                        min_dist_ind = j

            hotspot = EnvFactor(x[min_dist_ind],y[min_dist_ind], i, sigma=init_sigma[i])
            self.envFactors.append(hotspot)
            x[min_dist_ind] = -1
            y[min_dist_ind] = -1
            ind = min_dist_ind
            i += 1

    def reduce_sigma(self):
        mu, sigma = .2, 0.02
        s = np.random.normal(mu, sigma, NUM_OF_HOTSPOTS)
        for i,envFactor in enumerate(self.envFactors):
            envFactor.sigma -= s[i]



    def gen_map(self):

        colors = np.zeros((GRID_SIZE, GRID_SIZE))

        scale_factor = 10000000000
        n_nearest = int(self.num_of_hotspots / 5)

        sums_of_gauss = np.zeros((GRID_SIZE, GRID_SIZE))
        for i in range(0, GRID_SIZE):
            for j in range(0, GRID_SIZE):
                gauss = []
                for envFactor in self.envFactors:
                    val = scale_factor * envFactor.gaussian(i,j)
                    gauss.append(int(val))
                sums_of_gauss[i,j] = sum(gauss)
                inds = np.argpartition(gauss, -1*n_nearest)[-1* n_nearest:]
                ij_lam = 0
                for ind in inds:
                    ij_lam += self.envFactors[ind].lam
                ij_lam = int(ij_lam / n_nearest)
                colors[i,j] = ij_lam



        # Mark centers
        for envFactor in self.envFactors:
            i,j = envFactor.x0, envFactor.y0
            colors[i,j] = 0

        # Seed fragments:
        for i in range(self.size/2):
            x,y = np.random.randint(0, self.size), np.random.randint(self.size)
            colors[x,y] = -1


        return colors
        #plt.imshow(colors, interpolation='none', aspect='equal', cmap="gist_earth")

    def next_gen(self, m0):
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

        base_prob = 0.001

        for i in range(1, self.size-1):
            for j in range(1, self.size-1):
                c = count_surroundings(i,j)
                if (np.random.random() < c*base_prob):
                    m[i,j] = -1
                if (c > 5):
                    m[i,j] = -1

        return m
