
#include "Individual.h"
#include "Genome.h"
#include "Random.h"
#include "params_struct.h"

int Individual::id_counter = 0;

Individual::Individual(Random *random, params_s* params){
    this->id = this->id_counter++;
    this->params = params;
    this->random = random;
    this->genome = new Genome(this, this->random, this->params);
}

void Individual::get_initial_alleles(){

}

void Individual::migrate(){

}

void Individual::get_fitness(){

}

void Individual::choose_mate(){

}

void Individual::reproduce(Individual* mate){

}
