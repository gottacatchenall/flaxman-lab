
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

        // Initialization
        void allocate_individuals();
        void setup_initial_alleles();

        // Core methods
            // These are each called once per generation
        void migrate();
        void selection();
        void mating();
        void census_pop(int gen);
        void next_gen(int gen);

        // Miscellaneous utility methods
        void mark_patch_occupied(Patch* patch);
        void mark_patch_unoccupied(Patch* patch);
        bool on_board(int x, int y);
        std::vector<Patch*> get_surrounding_patches(int x, int y);

        // Getters and Setters
        Patch* get_patch(int x, int y);
        int get_envFactor_value(int x, int y, int envFactor);
        int get_total_num_indivs();

        // Testing and Validation
        #if __DEBUG__
            int check_num_of_indivs();
            void check_occupied_patches_vector();
        #endif

};

#endif
