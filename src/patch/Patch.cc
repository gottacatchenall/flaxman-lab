#include "Patch.h"
#include "Board.h"
#include "Individual.h"

Patch::Patch(int x, int y, Board* parentBoard){
    this->n_indiv = 0;
    this->x = x;
    this->y = y;
    this->parentBoard = parentBoard;
}

void Patch::add_individual(Individual* indiv){
    std::pair<int, Individual*> value (indiv->get_id(), indiv);
    this->indivs.insert(value);
    this->increment_num_indiv();
}

void Patch::remove_individual(Individual* indiv){
    this->indivs.erase(indiv->get_id());
}

void Patch::increment_num_indiv(){
    this->n_indiv++;
}

void Patch::decrement_num_indiv(){
    this->n_indiv--;
    assert(n_indiv >= 0);
}
