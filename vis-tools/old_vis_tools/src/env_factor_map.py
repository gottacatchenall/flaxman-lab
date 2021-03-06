#! /usr/bin/env python

import argparse
import csv
import os
import numpy as np
import glob, os

from plot_board import setup
from plot_board import show

def get_data(rel_path):
    abs_path = os.path.abspath(rel_path)

    os.chdir(abs_path)

    getdim = np.genfromtxt("envFactor0.csv", delimiter=',')
    dim = len(getdim)

    maps = np.zeros((len(os.listdir(abs_path)),dim,dim))

    for i,file in enumerate(os.listdir(abs_path)):
        if file.endswith(".csv"):
            with open(file, 'rU') as p:
                m = np.genfromtxt(p, delimiter=',')
            maps[i] = m
    return maps

def env_factor_map(rel_path=False):
    if rel_path == False:
        rel_path = 'envFactors/'
    maps = get_data(rel_path)

    size = len(maps[0])
    colorramp = np.linspace(0, 100, len(maps))

    colors = np.zeros((size,size))

    for i in range(0, size):
        for j in range(0, size):
            bin_array = np.zeros(len(maps))
            color = 0
            count = 0
            for k,m in enumerate(maps):
                if (m[i,j] == 1):
                    bin_array[k] = 1
                    count += 1

            for (b_index, val) in enumerate(bin_array):
                if (val == 1):
                    color += colorramp[b_index]

            colors[i,j] = color / count

    return colors
