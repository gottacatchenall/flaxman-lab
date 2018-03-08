
#include "Genome.h"
#include "params_struct.h"


Genome::Genome(Individual* individual, Random* random, params_s* params){
    this->individual = individual;
    this->random = random;
    this->params = params;

    this->K_VALUE = params->N_ENV_FACTORS;

    this->preferences = new int[K_VALUE];
    this->fitness = new int[K_VALUE];
    this->male_chromosome = new int[2];
    this->female_chromosome = new int[1];
}

Genome* Genome::mate(Genome* mate_genome){
    return mate_genome;
}

void Genome::crossing_over(Genome* a, Genome* b, Genome* result){

}
