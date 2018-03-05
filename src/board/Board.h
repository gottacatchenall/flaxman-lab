
#ifndef BOARD_H
#define BOARD_H

#include <assert.h>
#include "include.h"

class Tile;
class EnvFactor;
class Random;
class Logger;
class Fractal;
class Fragment;

class Board{
    private:
        int BOARD_SIZE;
        int N_ENV_FACTORS;

        // Random generator
        Random* random;
        Fractal* fractal;
        Logger* logger;

        // Array of environmental factors
        EnvFactor** envFactors;

        // Fragment
        Fragment *fragment;

        // Matrix of Tiles
        Tile ***grid;

    public:
        Board(Board* self, Random* random, Fractal* fractal, Logger* logger, int BOARD_SIZE, int N_ENV_FACTORS);
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
