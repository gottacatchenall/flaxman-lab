
#ifndef BOARD_H
#define BOARD_H

#include <assert.h>
#include "include.h"
#include <unordered_map>

// Forward Declarations
class Patch;
class EnvFactor;
class Random;
class Logger;
class Fractal;
class Fragment;
struct params_s;
typedef params_s params_s;
struct genetic_map_s;
typedef genetic_map_s genetic_map_s;

class Board{
    private:
        int BOARD_SIZE;
        int N_ENV_FACTORS;

        params_s* params;
        genetic_map_s* genetic_map;

        Random* random;
        Fractal* fractal;
        Logger* logger;

        // Array of environmental factors
        EnvFactor** envFactors;
        Fragment *fragment;

        // Matrix of Patches
        Patch ***grid;

        // Vector of occupied patches
        std::unordered_map<int, Patch*> occupied_patches;


    public:
        Board(Random* random, Fractal* fractal, Logger* logger, params_s* params, genetic_map_s* genetic_map);
        Patch* get_patch(int x, int y);
        int get_envFactor_value(int x, int y, int envFactor);
        void allocate_individuals();
        void setup_initial_alleles();
        void log_gen(int gen);
        void migrate();
        void next_gen(int gen);

};

#endif
