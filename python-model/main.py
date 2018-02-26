#! /usr/bin/env python

from board import Board

NUM_GEN = 1000

def main():
    board = Board()
    board.init_hotspots()
    m0 = board.gen_map()
    maps = [None for i in range(0, NUM_GEN)]
    maps[0] = m0

    for i in range(1, NUM_GEN):
        m = board.next_gen(maps[i-1])
        maps[i] = m

    board.show_board(maps)



if __name__ == '__main__':
    main()
