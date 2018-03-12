#include "Patch.h"
#include "Board.h"
#include "Individual.h"

Patch::Patch(int x, int y, Board* board){
    this->n_indiv = 0;
    this->x = x;
    this->y = y;
    this->board = board;
}

int Patch::get_x(){
    return this->x;
}

int Patch::get_y(){
    return this->y;
}

int Patch::get_envFactor_value(int x, int y, int envFactor){
    return this->board->get_envFactor_value(x, y, envFactor);
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
