
#ifndef BOARD_H
#define BOARD_H

#include <assert.h>
#include "Cell.h"
#include "EnvFactor.h"

struct point{
            int x;
            int y;
};

class Board{
    private:
        int BOARD_SIZE;
        int N_ENV_FACTORS;
        typedef std::vector<EnvFactor> vec_envFactor;
        vec_envFactor envFactors;
        typedef std::vector<std::vector<Cell>> matrix;
        matrix grid;
    public:
        Board(int BOARD_SIZE, int N_ENV_FACTORS);
        void init_envFactors();
        void allocate_individuals();
        void migrate();
        void next_gen();

};

#endif
