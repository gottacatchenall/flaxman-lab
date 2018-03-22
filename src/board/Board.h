
#ifndef BOARD_H
#define BOARD_H

#include "include.h"
#include <assert.h>
#include <unordered_map>

class Board{
    private:
        int BOARD_SIZE;
        int N_ENV_FACTORS;

        // Array of environmental factors
        EnvFactor** envFactors;
        Fragment *fragment;

        // Matrix of Patches
        Patch ***grid;

        // Vector of occupied patches
        std::unordered_map<int, Patch*> occupied_patches;
    public:
        Board();
        Patch* get_patch(int x, int y);
        std::vector<Patch*> get_surrounding_patches(int x, int y);
        bool on_board(int x, int y);
        int get_envFactor_value(int x, int y, int envFactor);
        void allocate_individuals();
        void setup_initial_alleles();
        void log_gen(int gen);
        void mark_patch_occupied(Patch* patch);
        void mark_patch_unoccupied(Patch* patch);
        void migrate();
        void next_gen(int gen);

};

#endif
