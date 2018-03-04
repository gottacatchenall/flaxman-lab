#! /usr/bin/env python
import pyximport
import numpy
pyximport.install(setup_args={"include_dirs":numpy.get_include()},
                  reload_support=True)

from rnd import Parent, Child

p = Parent()

p.make_child()

import numpy as np
from plot_board import setup
from plot_board import show

BOARD_SIZE = 16
ENV_FACTOR_H_VALUE = 0.8

def std_normal():
    val =  p.children[0].gen_uniform()
    #print val
    return val

def f4(delta, a, b, c, d):
  avg = ((a+b+c+d)/(4.0))
  val =  avg + delta * std_normal();
  return val

def f3(delta, a, b, c):
  val = (float(a+b+c)/float(3)) + delta * std_normal()
  return val

def generate_fractal():
  X = np.zeros((BOARD_SIZE+1,BOARD_SIZE+1))
  delta = 1.0
  N = BOARD_SIZE

  maxlevel = int(np.log2(BOARD_SIZE))

  H = ENV_FACTOR_H_VALUE

  D = N
  d = N/2

  # Init corner values
  X[0][0] = delta*std_normal()
  X[0][N] = delta*std_normal()
  X[N][0] = delta*std_normal()
  X[N][N] = delta*std_normal()

  for stage in range(0, maxlevel):
    print("---STAGE: " + str(stage))
    delta = delta * np.power(0.5, (0.5*H))
    print 'delta = ' + str(delta)
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
      print "X[" + str(x) + "[0] = " + str(X[x][0])
      print "X[" + str(x) + "][" + str(N) +"] = " + str(X[x][N])
      print "X[0][" + str(x) + "] = " + str(X[0][x])
      print "X[" +str(N) + "][" +str(x) + "] = " + str(X[N][x])
      print ''

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

  M = np.zeros((BOARD_SIZE,BOARD_SIZE))

  for i in range(0, BOARD_SIZE):
    for j in range(0, BOARD_SIZE):
        if (X[i][j] > 0):
            M[i][j] = 0
        else:
            M[i][j] = 1

  return M

m = generate_fractal()
fig, ax = setup(BOARD_SIZE)
show(fig, ax, m)
