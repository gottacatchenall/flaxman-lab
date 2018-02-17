#! /usr/bin/env python

from board import Board

NUM_GEN = 100

def main():
    board = Board()
    board.init_hotspots()

    maps = [None for i in range(0, NUM_GEN)]
    for i in range(0, NUM_GEN):
        m = board.calc_lam(i)
        maps[i] = m
        board.reduce_sigma()

    for i in range(1, NUM_GEN):
        if (maps[i].all() == maps[i-1].all()):
            print 'same'

    board.show_board(maps)



if __name__ == '__main__':
    main()
