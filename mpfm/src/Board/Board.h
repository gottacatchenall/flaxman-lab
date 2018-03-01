
#ifndef BOARD_H
#define BOARD_H

#include "EnvFactor.h"
#include "Cell.h"
#include <assert.h>

struct point{
            int x;
            int y;
};

class Board{
    private:
        int BOARD_SIZE;
        int N_ENV_FACTORS;
        Board* self_addr;

        // Array of environmental factors
        typedef std::vector<EnvFactor> vec_envFactor;
        vec_envFactor envFactors;

        // Matrix of cells
        typedef std::vector<std::vector<Cell>> matrix;
        matrix grid;
    public:
        Board(int BOARD_SIZE, int N_ENV_FACTORS);
        void set_address(Board* addr);
        void init_cells();
        void init_envFactors();
        void allocate_individuals();
        void migrate();
        void next_gen();
        void print_hello();


};

#endif
