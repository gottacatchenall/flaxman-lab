
#ifndef ENVFACTOR_H
#define ENVFACTOR_H

#include "include.h"
#include <vector>

class EnvFactor{
    private:
        int id;
        int BOARD_SIZE;
        double H_VALUE;
        double CUTOFF;
        int** envFactor_grid;
    public:
        EnvFactor(int index);
        void set_cell_value(int x, int y, int val);
        int get_cell_value(int x, int y);
        int get_id();
        int get_board_size();
};

#endif
