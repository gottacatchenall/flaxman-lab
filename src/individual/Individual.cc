
#include "Individual.h"
#include "Genome.h"
#include "Random.h"
#include "Patch.h"
#include "params_struct.h"
#include "genetic_map.h"

int Individual::id_counter = 0;

Individual::Individual(Patch* patch, Random* random, params_s* params, genetic_map_s* genetic_map){
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

    // Ancestral Genotype
    if (this->params->INDIVIDUALS_INITIAL_GENOME == INDIVIDUALS_ANCESTRAL_GENOTYPE){
        //int K_VALUE = this->params->N_ENV_FACTORS;
    }

    // Perfectly Adapted Genome
    else if (this->params->INDIVIDUALS_INITIAL_GENOME == INDIVIDUALS_PERFECTLY_ADAPTED_GENOTYPE){
        int K_VALUE = this->params->N_ENV_FACTORS;
        int allele, fit_locus;
        for (int i = 0; i < K_VALUE; i++){
            allele = this->patch->get_envFactor_value(this->patch->get_x(), this->patch->get_y(), i);
            fit_locus = this->genetic_map->fitness_loci[i];
            this->genome->set_allele(fit_locus, allele);
        }

        #if __DEBUG__
            int env_val;
            for (int i = 0; i < K_VALUE; i++){
                fit_locus = this->genetic_map->fitness_loci[i];
                env_val = this->patch->get_envFactor_value(this->patch->get_x(), this->patch->get_y(), i);
                if (this->genome->get_allele(fit_locus) != env_val){
                    assert(0 && "genome init failed");
                }
            }
        #endif
    }

    // Entirely Random Genotype
    else if (this->params->INDIVIDUALS_INITIAL_GENOME == INDIVIDUALS_RANDOM_GENOTYPE){
        int i;
        double allele;
        for (i = 0; i < this->params->N_LOCI; i++){
            allele = this->random->uniform_float(0.0, 1.0);
            this->genome->set_allele(i, allele);
        }
    }
}

double Individual::get_allele(int locus){
    return this->genome->get_allele(locus);
}

void Individual::migrate(){

}

void Individual::get_fitness(){

}

void Individual::choose_mate(){

}

void Individual::reproduce(Individual* mate){

}
