#! /usr/bin/env python

from plot_board import setup, show
import numpy as np

BOARD_SIZE = 32
NUM_AXES = 4
N_POINTS = 10
BASE_PROB = .003

N_GEN = 1000

def generate_fractal(CUTOFF):
  def std_normal():
    val =  np.random.normal(0,1)
    return val
  def f4(delta, a, b, c, d):
      avg = ((a+b+c+d)/(4.0))
      val =  avg + delta * std_normal();
      return val

  def f3(delta, a, b, c):
      val = (float(a+b+c)/float(3)) + delta * std_normal()
      return val
  X = np.zeros((BOARD_SIZE+1,BOARD_SIZE+1))
  delta = 1.0
  N = BOARD_SIZE

  maxlevel = int(np.log2(BOARD_SIZE))

  H = 0.1

  D = N
  d = N/2

  # Init corner values
  X[0][0] = delta*std_normal()
  X[0][N] = delta*std_normal()
  X[N][0] = delta*std_normal()
  X[N][N] = delta*std_normal()

  for stage in range(0, maxlevel):
    delta = delta * np.power(0.5, (0.5*H))
    # interpolate and offset points
    for x in range(d, N-d+1, D):
      for y in range(d, N-d+1,D):
        X[x][y] = f4(delta, X[x+d][y+d], X[x+d][y-d], X[x-d][y+d],X[x-d][y-d])
        #print 'X[' + str(x) + '][' + str(y) + '] = ' + str(X[x][y])

    delta = delta * (pow(0.5, 0.5*H))

    # boundary grid points
    for x in range(d, N-d+1, D):
      X[x][0] = f3(delta, X[x+d][0], X[x-d][0], X[x][d])
      X[x][N] = f3(delta, X[x+d][N], X[x-d][N], X[x][N-d])
      X[0][x] = f3(delta, X[0][x+d], X[0][x-d], X[d][x])
      X[N][x] = f3(delta, X[N][x+d], X[N][x-d], X[N-d][x])

    # interpolate and offset interior grid points

    for x in range(d, N-d+1, D):
      for y in range(D, N-d+1,D):
        X[x][y] = f4(delta, X[x][y+d], X[x][y-d], X[x+d][y], X[x-d][y])


    for x in range(D,N-d+1,D):
      for y in range(d, N-d+1, D):
        X[x][y] = f4(delta, X[x][y+d], X[x][y-d], X[x+d][y], X[x-d][y])


    D = D/2;
    d = d/2;


  #print X

  m = np.zeros((BOARD_SIZE,BOARD_SIZE))

  for i in range(0, BOARD_SIZE):
    for j in range(0, BOARD_SIZE):
        if (X[i][j] > CUTOFF):
            m[i][j] = 0
        else:
            m[i][j] = 1



  return m

def fractal():

    c = 0
    frac = 0
    lo_cutoff = 1
    m = np.ones((BOARD_SIZE,BOARD_SIZE))


    loopct= 0
    while (frac < 0.3 or frac > 0.4):
        c = 0
        if (frac < 0.4):
            mn = generate_fractal(lo_cutoff)
            for i in range(BOARD_SIZE):
                for j in range(BOARD_SIZE):
                    if (mn[i,j] == 0):
                        m[i,j] = 0
        elif (frac > 0.4):
            mn = generate_fractal(lo_cutoff)
            for i in range(BOARD_SIZE):
                for j in range(BOARD_SIZE):
                    if (mn[i,j] == 0):
                        m[i,j] = 1


        for i in range(BOARD_SIZE):
            for j in range(BOARD_SIZE):
                if m[i,j] > 1:
                    m[i,j] = 1
                if m[i,j] == 0:
                    c += 1
        frac = float(c) / float(BOARD_SIZE**2)
        loopct += 1
        if (loopct > 10):
            break

    return m

m = fractal()

maps = np.ones((N_GEN, BOARD_SIZE, BOARD_SIZE))
base_prob = 0.01
for gen in range(1,N_GEN):
    tmp = maps[gen-1]

    for i in range(BOARD_SIZE):
        for j in range(BOARD_SIZE):
            if m[i,j] == 0:
                # not yet marked
                if tmp[i,j] == 1:
                    if (np.random.rand() < base_prob):
                        tmp[i,j] = 0

    maps[gen] = tmp


fig, ax = setup(BOARD_SIZE)
show(fig, ax, maps, ani=True)
