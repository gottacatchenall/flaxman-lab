
#ifndef ENVFACTOR_H
#define ENVFACTOR_H

#include <vector>
#include "include.h"

class EnvFactor{
    private:
      int id;
      int x0;
      int y0;
      int BOARD_SIZE;
      int** envFactor_grid;
    public:
      EnvFactor(int index, int x0, int y0, int BOARD_SIZE);
      void run_random_walk();
      int count_surrounding_ones(int x, int y);
      void set_cell_value(int x, int y, int val);
      int get_cell_value(int x, int y);
      void print_env_factor();
};

#endif
