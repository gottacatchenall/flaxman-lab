#include "Patch.h"
#include "Board.h"
#include "Individual.h"
#include "bio_functions.h"
#include "params_struct.h"

Patch::Patch(Board *board, params_s* params, int x, int y){
    this->n_indiv = 0;
    this->x = x;
    this->y = y;
    this->board = board;
    this->params = params;
}

void Patch::setup_initial_alleles(){
    int num_alleles = expected_num_neutral_alleles(this->n_indiv, params->MUTATION_RATE);
    printf("num alleles: %d\n", num_alleles);
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

std::vector<Individual*> Patch::get_all_individuals(){
    int ct = this->indivs.size();

    std::vector<Individual*> individuals;

    if (ct < 1){
        return individuals;
    }

    Individual* tmp_indiv;
    for (auto ind: this->indivs){
        tmp_indiv = ind.second;
        individuals.push_back(tmp_indiv);
    }

    return individuals;
}

void Patch::increment_num_indiv(){
    this->n_indiv++;
}

void Patch::decrement_num_indiv(){
    this->n_indiv--;
    assert(n_indiv >= 0);
}
