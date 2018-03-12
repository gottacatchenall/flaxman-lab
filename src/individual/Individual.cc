
#include "Individual.h"
#include "Genome.h"
#include "Random.h"
#include "Patch.h"
#include "params_struct.h"

int Individual::id_counter = 0;

Individual::Individual(Patch* patch, Random *random, params_s* params){
    this->id = this->id_counter++;
    this->params = params;
    this->random = random;
    this->patch = patch;
    this->genome = new Genome(this, this->random, this->params);
}

int Individual::get_id(){
    return this->id;
}

void Individual::get_initial_alleles(){
    if (this->params->INDIVIDUALS_INITIAL_GENOME == INDIVIDUALS_ANCESTRAL_GENOTYPE){

    }
    else if (this->params->INDIVIDUALS_INITIAL_GENOME == INDIVIDUALS_PERFECTLY_ADAPTED_GENOTYPE){
        assert(0 && "not implemented yet");
    }
    else if (this->params->INDIVIDUALS_INITIAL_GENOME == INDIVIDUALS_RANDOM_GENOTYPE){
        assert(0 && "not implemented yet");
    }
}

void Individual::migrate(){

}

void Individual::get_fitness(){

}

void Individual::choose_mate(){

}

void Individual::reproduce(Individual* mate){

}
