#! /usr/bin/env python

import numpy as np
import csv

def read_fragmentation_data(abs_path):
    with open(abs_path, 'rU') as p:
        csvdata = np.genfromtxt(p, delimiter=',')
        #csvfile = csv.reader(p, delimiter=',')
        #length = sum(1 for row in csvfile)

    return csvdata
    #tmp = [list(map(int,rec)) for rec in csv.reader(p, delimiter=',')]
