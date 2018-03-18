#! /usr/bin/env python

import numpy as np


def exp_num_alleles(theta, n):
    res = 0
    for i in range(n-1):
        res += float(theta) / float(theta+1)
    return res

def get_allele_distr(N,N_alleles):
    rem = 1
    p = []

    for i in range(N_alleles-1):
        prop_rem = np.random.beta(0.6, 1.7)
        prop_total = rem * prop_rem
        p.append(prop_total)
        rem -= prop_total
    p.append(rem)

    n_with_each = []

    for i in range(len(p)):
        n_with_each.append(int(p[i] * N))


    afs = np.zeros(max(n_with_each)+1)
    for n in n_with_each:
        if (n > 0):
            afs[n] += 1
    return afs

def ewens(afs, theta):
    n = len(afs)
    nfac = np.math.factorial(n)

    theta_prod = 1
    for i in range(n):
        theta_prod = theta_prod * (theta+i)

    big_prod = 1
    for j,m_j in enumerate(afs):
        big_prod = big_prod * float(theta ** m_j) / float((j**m_j) * np.math.factorial(m_j))

    val = float(nfac * big_prod) / float(theta_prod)
    return val


N = 30
mu = 0.01
theta = 4 * N * mu

maxprob = 0
max_alpha = 0
max_beta = 0

n_alleles = int(np.floor(exp_num_alleles(theta, N)))
afs = get_allele_distr(N,n_alleles)
p = ewens(afs, theta)

print p
