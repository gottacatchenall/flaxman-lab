
#include "Genome.h"
#include "params_struct.h"


Genome::Genome(Individual* individual, Random* random, params_s* params){
    this->individual = individual;
    this->random = random;
    this->params = params;

    this->K_VALUE = params->N_ENV_FACTORS;

    this->N_CHROMOSOMES = params->N_CHROMOSOMES;
    this->N_LOCI = params->N_LOCI;


    this->genome = new int[this->N_LOCI];
    this->genetic_map = new int[this->N_CHROMOSOMES];

    this->pref_loci = new int[this->K_VALUE];
    this->fitness_loci = new int[this->K_VALUE];
    this->male_loci = new int[2];
    this->female_loci = new int[1];

}

Genome* Genome::mate(Genome* mate_genome){
    return mate_genome;
}

void Genome::crossing_over(Genome* a, Genome* b, Genome* result){

}
