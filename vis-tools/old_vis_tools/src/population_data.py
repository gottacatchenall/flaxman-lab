import argparse
import csv
import os
import numpy as np
import glob, os

def population_data(abs_path):
    #maps = get_data(abs_path)
    maps = []
    os.chdir(abs_path)
    dirs = glob.glob('*')
    for dir in dirs:
        print dir
        file = dir + '/generation_map.csv'
        with open(file, 'rU') as p:
            m = np.genfromtxt(p, delimiter=',')
            maps.append({'gen': int(dir), 'map': m})
    maps.sort(key=lambda x: x['gen'])
    return maps
