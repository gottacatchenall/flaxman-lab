#! /usr/bin/env python

import argparse
import csv
import os
import numpy as np
import glob, os
from scipy import stats
import matplotlib.patches as patches
import matplotlib.pyplot as plt


#fitness_loci = [ 5, 6, 12, 18, 18, 33, 36, 37, 55, 58, 60, 62, 68, 73, 74, 76 ]
fitness_loci = [ 0, 1, 13, 28, 39, 40, 60, 70 ]
n_loci = 80

all_data = []

def ld_data(file_name):

    ld_time_series = []
    fitness_ld_time_series = []

    dirs = glob.glob('*')
    for dir in dirs:
        file = dir + '/' + file_name
        sum = 0
        fitness_sum = 0
        fitness_ct = 0
        ct = 0

        lds = []
        try:
            with open(file, mode='r') as infile:
                reader = csv.reader(infile)
                for rows in reader:
                    all_data.append(rows)
                    lds.append(abs(float(rows[4])))
                sd = stats.sem(lds)
                sevfth = np.percentile(lds, 75)
                twfth = np.percentile(lds, 25)
                mean = np.mean(lds)
                gen = int(dir)
                ld_time_series.append({'sd': sd, 'mean': mean, 'gen': gen, 'sevfth':sevfth, 'twfth':twfth})
        except:
            print 'nope'

    return ld_time_series

def plot_range(ld, color):
    x_v = [float(x['gen']) for x in ld]

#    y1 = [float(x['twfth']) for x in ld]
#    y2 = [float(x['sevfth']) for x in ld]
    y1 = [float(x['mean'])-float(x['sd']) for x in ld]
    y2 = [float(x['mean'])+float(x['sd']) for x in ld]
    plt.fill_between(x_v, y1, y2, where=y2 >= y1, facecolor=color, alpha=0.4, interpolate=False)

def plot():
    plt.plot([x['gen'] for x in ld], [x['mean'] for x in ld], label="all loci", color="darkblue")
    plt.plot([x['gen'] for x in ld_fitness], [x['mean'] for x in ld_fitness], label="fitness loci", color="red")


    plt.axvline(x=2000, color='black', linestyle='--')
    plt.axvline(x=5000, color='black', linestyle='--')

    plt.grid(lw=1)
    plt.xticks([0,2500,5000,7500,10000])
    plt.ylim([0, 0.02])
    plt.xlim([0,10000])
    #plt.axis('scaled')

    plot_range(ld, 'blue')
    plot_range(ld_fitness, 'red')
    plt.legend()
    plt.ylabel("LD")
    plt.xlabel("generation")
    plt.show()

def max_ld_by_locus():
    max_ld = [0.0 for x in range(n_loci)]

    for ld_val in all_data:
        l1 = int(ld_val[0])
        l2 = int(ld_val[2])
        ld = abs(float(ld_val[4]))
        if ld > max_ld[l1]:
            max_ld[l1] = ld
        if ld > max_ld[l2]:
            max_ld[l2] = ld

    for val in fitness_loci:
        #plt.Rectangle((int(val),1),5,10,linewidth=1,alpha=0.7,edgecolor='grey',facecolor='grey')
        plt.scatter(val,max_ld[val], color='black', linestyle='--')

    plt.axhline(np.mean(max_ld), color='black', linestyle='--')

    plt.plot([i for i in range(len(max_ld))], max_ld)
    plt.show()

#max_ld_by_locus()

os.chdir(os.path.abspath('./generations/'))

ld = ld_data("ld.csv")
ld_fitness = ld_data("fitness_ld.csv")


ld.sort(key=lambda x: x['gen'])
ld_fitness.sort(key=lambda x: x['gen'])
#plot()
max_ld_by_locus()
