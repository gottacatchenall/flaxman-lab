#include "Patch.h"
#include "Board.h"

Patch::Patch(int x, int y, Board* parentBoard){
    this->n_indiv = 0;
    this->x = x;
    this->y = y;
    this->parentBoard = parentBoard;
}

void Patch::increment_num_indiv(){
    this->n_indiv++;
}

void Patch::decrement_num_indiv(){
    this->n_indiv--;
    assert(n_indiv >= 0);
}
