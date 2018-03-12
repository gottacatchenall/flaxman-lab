
#include "Genome.h"
#include "params_struct.h"


Genome::Genome(Individual* individual, Random* random, params_s* params){
    this->individual = individual;
    this->random = random;
    this->params = params;

    this->K_VALUE = params->N_ENV_FACTORS;

    this->N_CHROMOSOMES = params->N_CHROMOSOMES;
    this->N_LOCI = params->N_LOCI;


    this->genome = new double[this->N_LOCI];

    for (int i = 0; i < this->N_LOCI; i++){
        this->genome[i] = 0.0;
    }
}

double Genome::get_allele(int locus){
    return this->genome[locus];
}

void Genome::set_allele(int locus, double value){
    this->genome[locus] = value;
}



Genome* Genome::mate(Genome* mate_genome){
    return mate_genome;
}

void Genome::crossing_over(Genome* a, Genome* b, Genome* result){

}
