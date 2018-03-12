
#include "Individual.h"
#include "Genome.h"
#include "Random.h"
#include "Patch.h"
#include "params_struct.h"
#include "genetic_map.h"

int Individual::id_counter = 0;

Individual::Individual(Patch* patch, Random *random, params_s* params, genetic_map_s* genetic_map){
    this->id = this->id_counter++;
    this->params = params;
    this->random = random;
    this->patch = patch;
    this->genetic_map = genetic_map;
    this->genome = new Genome(this, this->random, this->params);
}

int Individual::get_id(){
    return this->id;
}

void Individual::get_initial_alleles(){
    if (this->params->INDIVIDUALS_INITIAL_GENOME == INDIVIDUALS_ANCESTRAL_GENOTYPE){
        int K_VALUE = this->params->N_ENV_FACTORS;



    }
    else if (this->params->INDIVIDUALS_INITIAL_GENOME == INDIVIDUALS_PERFECTLY_ADAPTED_GENOTYPE){
        int K_VALUE = this->params->N_ENV_FACTORS;
        int allele, fit_locus;
        for (int i = 0; i < K_VALUE; i++){
            allele = this->patch->get_envFactor_value(this->patch->get_x(), this->patch->get_y(), i);
            fit_locus = this->genetic_map->fitness_loci[i];
            this->genome->set_allele(fit_locus, allele);
        }
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
