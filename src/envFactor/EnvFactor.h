
#ifndef ENVFACTOR_H
#define ENVFACTOR_H

#include <vector>
#include "include.h"

class Random;

class EnvFactor{
    private:
      int id;
      int BOARD_SIZE;
      int** envFactor_grid;
      Random* random;
    public:
      EnvFactor(Random* random, int index, int BOARD_SIZE);
      void set_cell_value(int x, int y, int val);
      int get_cell_value(int x, int y);
      int get_id();
      int get_board_size();
      void run_random_walk();
      void generate_fractal();
      double f4(double delta, double a, double b, double c, double d);
      double f3(double delta, double a, double b, double c);
      int count_surrounding_ones(int x, int y);
      void print_env_factor();
};

#endif
