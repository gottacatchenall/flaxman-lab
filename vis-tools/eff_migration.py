#! /usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np
import argparse, csv, os, glob
from scipy import stats

def get_data(rel_path):
    abs_path = os.path.abspath(rel_path + '/generations')
    maps = []
    dirs = glob.glob(abs_path + '/*')
    for dir in dirs:
        gen_num = dir.rsplit('/', 1)[-1]
        file = dir + '/eff_migration.csv'
        with open(file, 'rU') as p:
            m = np.genfromtxt(p, delimiter=',', dtype=float)
            maps.append({'gen': int(gen_num), 'map': m})
    maps.sort(key=lambda x: x['gen'])
    return maps

def get_avg_by_gen(data):
    x = []
    avgs = []
    n = len(data[0]['map'])

    for matrix in data:
        if matrix['gen'] > 0:
            ct = 0
            sum = 0
            for i in range(n):
                for j in range(n):
                    if not np.isnan(matrix['map'][i][j]) and matrix['map'][i][j] < 1.0:
                        ct += 1
                        sum += matrix['map'][i][j]
            x.append(matrix['gen'])
            avgs.append(float(sum)/float(ct))
            #avgs.append(np.nanmean(matrix['map']))
    return x,avgs

data = get_data('.')

x,y = get_avg_by_gen(data)

slope, intercept, r_value, p_value, std_err = stats.linregress(x,y)


plt.plot(x, [slope*i+intercept for i in x], color='green')
plt.scatter(x,y, label="5ef, 3 loci per ef", color='dodgerblue')

plt.title('Average Effective Migration Rate')
plt.xlabel('Generation')
plt.ylabel('Avg Eff Migration Rate')

plt.legend()
plt.show()

#five_locus_data = get_data(five_locus_path)
#single_locus_data = get_data(single_locus_path)
