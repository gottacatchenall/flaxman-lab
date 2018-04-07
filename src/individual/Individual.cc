
#include "Individual.h"
#include "Random.h"
#include "Patch.h"
#include "params_struct.h"
#include "genetic_map.h"

int Individual::id_counter = 0;

Individual::Individual(Patch* patch, int sex){
    this->id = this->id_counter++;
    this->sex = sex;
    this->patch = patch;

    int n_loci = params->N_LOCI;
    this->haplotype1 = new double[n_loci];
    this->haplotype2 = new double[n_loci];
}

void Individual::set_haplotype(int haplo_num, double* haplotype){
    if (haplo_num == 1){
        free(this->haplotype1);
        this->haplotype1 = haplotype;
        return;
    }
    else if (haplo_num == 2){
        free(this->haplotype2);
        this->haplotype2 = haplotype;
        return;
    }

    assert(0 && "set_haplotype called with invalid haplo_num");
}

int Individual::get_id(){
    return this->id;
}

int Individual::get_sex(){
    return this->sex;
}

void Individual::set_allele(int locus, double value, int haplo){
    if (haplo == 1){
        this->haplotype1[locus] = value;
    }
    else{
        this->haplotype2[locus] = value;
    }
}

double Individual::get_allele(int locus, int haplo){
    if (haplo == 1){
        return this->haplotype1[locus];
    }
    return this->haplotype2[locus];
}

// ==========================================
// Selection
// ==========================================
double Individual::fitness_gaussian(double diff){
    double sigma = params->SELECTION_STRENGTH;
    return exp(-1*(diff*diff)/(2*sigma*sigma));
}

double Individual::calc_fitness(){
    int n_fitness_loci = params->N_ENV_FACTORS;
    double max_fitness = n_fitness_loci*2;
    int locus;
    double env_factor_val, allele_val, diff;

    double fitness = 0.0;

    for (int i = 0; i < n_fitness_loci; i++){
        locus = genetic_map->fitness_loci[i];
        env_factor_val = this->patch->get_envFactor_value(i);

        allele_val = this->get_allele(locus, 1);
        diff = env_factor_val - allele_val;
        fitness += this->fitness_gaussian(diff);

        allele_val = this->get_allele(locus, 2);
        diff = env_factor_val - allele_val;
        fitness += this->fitness_gaussian(diff);
    }

    double norm_fitness = fitness/max_fitness;
    return norm_fitness;
}

double Individual::beverton_holt_prob(double k_prime){
    int n = this->patch->get_n_indiv();
    int b = params->AVG_NUM_OFFSPRING_PER_FEMALE;

    double prop_full = double(n)/double(k_prime);
    double prob = double(1.0) / double(1 + (double(b)/double(2) - 1)*(prop_full));
    return prob;
}

bool Individual::selection(){
    double fitness = this->calc_fitness();
    double k_prime = double(params->CARRYING_CAPACITY * fitness);
    double prob = this->beverton_holt_prob(k_prime);

    if (random_gen->uniform_float(0,1) < prob){
            return true;
    }
    return false;
}

// ==========================================
// Migration
// ==========================================

double Individual::calc_pref(Patch* patch){
    double allele_val, env_factor_val;
    int locus;
    double pref = 1.0;
    double diff;
    int n_pref_loci= params->N_ENV_FACTORS;
    for (int i = 0; i < n_pref_loci; i++){
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

double* Individual::make_gamete(){
    double* gamete = new double[params->N_LOCI];

    if (params->LINKAGE_MODE == ALL_LOCI_INDEPENDENT){
        int n_loci = params->N_LOCI;
        int haplo;
        for (int i = 0; i < n_loci; i++){
            haplo = random_gen->uniform_int(0,1);
            gamete[i] = this->get_allele(i, haplo);
        }
        return gamete;
    }
    else if (params->LINKAGE_MODE == NORMAL_LINKAGE){
        return gamete;
    }

    assert(0 && "neither linkage mode was chosen");
}
