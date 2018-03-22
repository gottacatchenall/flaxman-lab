
#include "Individual.h"
#include "Genome.h"
#include "Random.h"
#include "Patch.h"
#include "params_struct.h"
#include "genetic_map.h"

int Individual::id_counter = 0;

Individual::Individual(Patch* patch){
    this->id = this->id_counter++;
    this->patch = patch;
    this->genome = new Genome(this);
}

int Individual::get_id(){
    return this->id;
}

void Individual::set_allele(int locus, double value, int haplo){
    this->genome->set_allele(locus, value, haplo);
}

double Individual::get_allele(int locus, int haplo){
    return this->genome->get_allele(locus, haplo);
}

double Individual::calc_pref(Patch* patch){
    double allele_val, env_factor_val;
    int locus;
    double pref = 1.0;
    double diff;
    int n_pref_alleles = params->N_ENV_FACTORS;
    for (int i = 0; i < n_pref_alleles; i++){
        locus = genetic_map->pref_loci[i];
        env_factor_val = patch->get_envFactor_value(i);

        allele_val = this->get_allele(locus, 1);

        diff = abs(allele_val - env_factor_val);
        pref = pref * diff;

        allele_val = this->get_allele(locus, 2);
        diff = abs(allele_val - env_factor_val);
        pref = pref * diff;
    }
    
    return pref;
}

void Individual::migrate(std::vector<Patch*> surrounding_patches){

    // Probability that an individual will migrate.
        // This can be done before finding out if there is a patch the individual
        // wants to migrate to because there will still be a MIGRATION_TENDENCY
        // proportion of indivs who could migrate but don't. Done to speed up runtime a bit.

    if (random_gen->uniform_float(0.0, 1.0) < params->MIGRATION_TENDENCY){
        return;
    }


    double pref;

    double min_pref = this->calc_pref(this->patch);
    Patch* best_patch = this->patch;

    for (Patch* patch : surrounding_patches){
        pref = this->calc_pref(patch);
        if (pref < min_pref){
            min_pref = pref;
            best_patch = patch;
        }
    }

    if (this->patch != best_patch){
        this->patch->remove_individual(this);
        best_patch->add_individual(this);
        this->patch = best_patch;
    }
}

void Individual::get_fitness(){

}

void Individual::choose_mate(){

}

void Individual::reproduce(Individual* mate){

}
