
#ifndef BOARD_H
#define BOARD_H

#include <assert.h>
#include "include.h"

class Tile;
class EnvFactor;

class Board{
    private:
        int BOARD_SIZE;
        int N_ENV_FACTORS;
        int ENV_FACTOR_MODE;

        // Array of environmental factors
        EnvFactor** envFactors;

        // Matrix of Tiles
        Tile ***grid;

    public:
        Board(Board* self, int BOARD_SIZE, int N_ENV_FACTORS, int ENV_FACTOR_MODE);
        Tile* get_tile(int x, int y);
        int** get_envFactor_points();
        void get_random_envFactor_points(int **points);
        void get_niche_envFactor_points(int **points);
        void get_gradient_envFactor_points(int **points);
        void init_envFactors();
        void allocate_individuals();
        void migrate();
        void next_gen();

};

#endif
