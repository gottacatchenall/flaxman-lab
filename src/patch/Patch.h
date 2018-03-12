
#ifndef PATCH_H
#define PATCH_H

#include <unordered_map>
#include "include.h"

class Individual;
class Board;

class Patch{
    private:
        int x;
        int y;
        int n_indiv;

        Board *parentBoard;

        // HASHTABLE of individuals on the tile.
        // KEY is the individual's id
        std::unordered_map<int, Individual*> indivs;
        void increment_num_indiv();
        void decrement_num_indiv();
    public:
        Patch(int x, int y, Board *parentBoard);
        void add_individual(Individual* indiv);
        void remove_individual(Individual* indiv);
};

#endif
