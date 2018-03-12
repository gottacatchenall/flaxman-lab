
#ifndef BOARD_H
#define BOARD_H

#include <assert.h>
#include "include.h"

// Forward Declarations
class Patch;
class EnvFactor;
class Random;
class Logger;
class Fractal;
class Fragment;
struct params_s;
typedef params_s params_s;

class Board{
    private:
        int BOARD_SIZE;
        int N_ENV_FACTORS;

        params_s* params;

        Random* random;
        Fractal* fractal;
        Logger* logger;

        // Array of environmental factors
        EnvFactor** envFactors;
        Fragment *fragment;

        // Matrix of Patches
        Patch ***grid;

    public:
        Board(Random* random, Fractal* fractal, Logger* logger, params_s* params);
        Patch* get_patch(int x, int y);
        int** get_envFactor_points();
        void allocate_individuals();
        void migrate();
        void next_gen(int gen);

};

#endif
