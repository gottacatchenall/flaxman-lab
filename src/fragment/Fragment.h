
#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "include.h"

class Random;
class Fractal;

class Fragment{
    private:
      int BOARD_SIZE;
      int** fragment_grid;
      Fractal* fractal;
      Random* random;
    public:
      Fragment(Random* random, Fractal* fractal, int BOARD_SIZE);
      void fragment_more();
      int get_board_size();
      void set_cell_value(int x, int y, int val);
      int get_cell_value(int x, int y);
};

#endif
