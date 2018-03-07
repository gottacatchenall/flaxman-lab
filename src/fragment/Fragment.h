
#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "include.h"

class Random;
class Fractal;
struct params_s;
typedef params_s params_s;

class Fragment{
    private:
      int BOARD_SIZE;
      float FRAGMENT_AMOUNT_LOW;
      float FRAGMENT_AMOUNT_HI;
      float FRAGMENT_H_VALUE;
      int** fragment_grid;
      Fractal* fractal;
      Random* random;
    public:
      Fragment(Random* random, Fractal* fractal,  params_s* params);
      int** create_fragment_map();
      int count_zeros(int **map);
      void fragment_more();
      int get_board_size();
      void set_cell_value(int x, int y, int val);
      int get_cell_value(int x, int y);
};

#endif
