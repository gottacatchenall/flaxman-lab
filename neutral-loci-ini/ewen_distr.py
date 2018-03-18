#! /usr/bin/env python

import numpy as np
import copy

### Construct a pseudodistribution of all possible afs's that could exist given a
### known number of alleles are present

def count_indiv(afs):
    s = 0
    for n,k in afs:
        s += (n) * k
    return s

def ewens(afs, theta):
    n = len(afs)
    nfac = np.math.factorial(n)

    theta_prod = 1
    for i in range(n):
        theta_prod = theta_prod * (theta+i)

    big_prod = 1
    for (m_j, j) in afs:
        big_prod = big_prod * float(theta ** m_j) / float((j**m_j) * np.math.factorial(m_j))
    val = float(nfac * big_prod) / float(theta_prod)
    return val

def exp_num_alleles(theta, n):
    res = 0
    for i in range(n-1):
        res += float(theta) / float(theta+1)
    return res


N = 40
mu = 0.01
theta = 4*N*mu

denominations = [x for x in range(1,N+1)]

tmp_afs = []

def count_combs(left, i, comb, add):
    if add: comb.append(add)
    if left == 0 or (i+1) == len(denominations):
        if (i+1) == len(denominations) and left > 0:
            comb.append( (left, denominations[i]) )
            i += 1
        while i < len(denominations):
            comb.append( (0, denominations[i]) )
            i += 1
        tmp_afs.append(comb)
        return 1
    cur = denominations[i]
    return sum(count_combs(left-x*cur, i+1, comb[:], (x,cur)) for x in range(0, int(left/cur)+1))



count_combs(N, 0, [], None)

valid_afs = []
for p in tmp_afs:
    if (count_indiv(p) == N):
        valid_afs.append(p)


probs = []
for i in range(len(valid_afs)):
    prob = ewens(valid_afs[i], theta)
    probs.append(prob)


dist = np.zeros(len(probs))

dist[1] = probs[0]

for i in range(2, len(probs)):
    dist[i] = dist[i-1] + probs[i]

val = np.random.rand()
maxind = len(dist) - 1
ind = maxind
for i in range(maxind):
    if (dist[i] < val and val < dist[i+1]):
        ind = i

afs = valid_afs[ind]
print afs
print count_indiv(afs)
print ewens(afs, theta)
