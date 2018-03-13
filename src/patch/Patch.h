
#ifndef PATCH_H
#define PATCH_H

#include <unordered_map>
#include <vector>
#include "include.h"

class Board;
class Individual;

class Patch{
    private:
        int x;
        int y;
        int n_indiv;

        Board *board;

        // HASHTABLE of individuals on the tile.
        // KEY is the individual's id
        std::unordered_map<int, Individual*> indivs;
        void increment_num_indiv();
        void decrement_num_indiv();
    public:
        Patch(int x, int y, Board *board);
        int get_x();
        int get_y();
        int get_envFactor_value(int x, int y, int envFactor);
        void add_individual(Individual* indiv);
        void remove_individual(Individual* indiv);
        std::vector<Individual*> get_all_individuals();
};

#endif
