
#ifndef ENVFACTOR_H
#define ENVFACTOR_H

#include <vector>
#include "include.h"

class Random;
class Fractal;

class EnvFactor{
    private:
      int id;
      int BOARD_SIZE;
      double H_VALUE;
      double CUTOFF;
      int** envFactor_grid;
      Fractal* fractal;
      Random* random;
    public:
      EnvFactor(Random* random, Fractal* fractal, int index, int BOARD_SIZE, double H_VALUE, double CUTOFF);
      void set_cell_value(int x, int y, int val);
      int get_cell_value(int x, int y);
      int get_id();
      int get_board_size();
      void generate_fractal();
};

#endif
