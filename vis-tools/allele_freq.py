#! /usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np
import argparse, csv, os, glob

three_locus_path = '5k_3lociperk_1000gen_300cc'
five_locus_path = '3k_5lociperk_1000gen_300cc'
single_locus_path = '15k_single_locus'

def get_allele_avg(patch_file):
    with open(patch_file, 'rU') as p:
        m = np.genfromtxt(p, delimiter=',', dtype=float, usecols=2)
        mean = np.mean(m)
        return mean



def get_data(rel_path):
    abs_path = os.path.abspath(rel_path + '/generations')
    avgs = []
    dirs = glob.glob(abs_path + '/*')
    for dir in dirs:
        gen_num = dir.rsplit('/', 1)[-1]
        patch_dirs = glob.glob(dir + '/patches/*')

        patch_avg = []
        if (len(patch_dirs) > 0):
            for patch_file in patch_dirs:
                patch_avg.append(get_allele_avg(patch_file))

            avgs.append({'mean': np.mean(patch_avg), 'gen': int(gen_num)})


    avgs.sort(key=lambda x: x['gen'])
    return avgs


three_locus_data = get_data(three_locus_path)
five_locus_data = get_data(five_locus_path)
one_locus_data = get_data(single_locus_path)

x = [i['gen'] for i in three_locus_data]
y_3l = [i['mean'] for i in three_locus_data]
y_5l = [i['mean'] for i in five_locus_data]
y_15l = [i['mean'] for i in one_locus_data]


plt.plot(x,y_3l, label="5ef, 3 loci per ef")
plt.plot(x,y_5l, label="3ef, 5 loci per ef")
plt.plot(x,y_15l, label="15ef, 1 locus per ef")

plt.title('Average Allele Freq')
plt.xlabel('Generation')
plt.ylabel('Avg Allele Freq Across All Loci')

plt.legend()
plt.show()
