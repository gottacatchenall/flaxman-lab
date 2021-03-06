#include "Patch.h"
#include "Board.h"
#include "Individual.h"
#include "Random.h"
#include "bio_functions.h"
#include "params_struct.h"
#include "genetic_map.h"
#include <algorithm>

Patch::Patch(Board *board, int x, int y){
    this->n_indiv = 0;
    this->max_fitness = 0.0;
    this->x = x;
    this->y = y;
    this->board = board;
    this->fragmented = false;
    this->indivs = new std::unordered_map<int, Individual*>;
    this->next_gen = new std::unordered_map<int, Individual*>;
    for (int i = 0; i < params->N_ENV_FACTORS; i++){
        this->envFactor_values.push_back(this->board->get_envFactor_value(this->x, this->y, i));
    }
}

// ==========================================
// Initialization
// ==========================================
  // these methods are only called before the simulation begins on patches with individuals in them

/*  Patch::setup_initial_alleles()
        Generates the allelic values and frequencies using the expected
        number of alleles given by Ewen's distribution, with allelic frequencies drawn
        for a beta distribution
*/
void Patch::setup_initial_alleles(){
    int N_LOCI = params->N_LOCI;
    std::vector<Individual*> indiv = this->get_all_individuals();


    // TODO this could be moved down to the individual level where alleles are
    // drawn from the distribution but don't completely conform to the proportions.

    for (int locus = 0; locus < N_LOCI; locus++){
        int n_this_locus = 2*this->n_indiv;
        int n_alleles = expected_num_neutral_alleles(n_this_locus, params->MUTATION_RATE);

        std::vector<double> props = this->generate_allele_freq_from_beta(n_alleles);
        std::vector<int> num_per_allele = this->get_num_with_each_allele(props, n_alleles, n_this_locus);
        std::vector<double> alleles = this->gen_alleles(n_alleles);

        std::vector<double> allele_map;
        for (int i = 0; i < n_alleles; i++){
            int n = num_per_allele[i];
            for (int j = 0; j < n; j++){
                allele_map.push_back(alleles[i]);
            }
        }

        random_shuffle(std::begin(allele_map), std::end(allele_map));

        int allele_ct = 0;
        for (int i = 0; i < this->n_indiv; i++){
            indiv[i]->set_allele(locus, allele_map[allele_ct], 0);
            allele_ct++;
            indiv[i]->set_allele(locus, allele_map[allele_ct], 1);
            allele_ct++;
        }


        #if __DEBUG__
            // Check that no individuals have 0 or 1 as an allele
            int zero, one;
            for (int i = 0; i < this->n_indiv; i++){
                zero = indiv[i]->get_allele(locus, 0);
                one = indiv[i]->get_allele(locus, 1);
                assert(zero != 0 && zero != 1 && one != 1 && one != 0);
            }
        #endif

    }
}

/*  Patch::generate_allele_freq_from_beta(int n_alleles)
        Generates the allelic frequencies in the population for n_alleles alleles from a beta distribution
*/
std::vector<double> Patch::generate_allele_freq_from_beta(int n_alleles){
    double rem = 1.0;
    double p, prop;
    std::vector<double> props;
    for (int i = 0; i < n_alleles - 1; i++){
        p = random_gen->beta(0.6, 1.7);
        prop = rem * p;
        rem -= prop;
        props.push_back(prop);
    }
    props.push_back(rem);
    return props;
}

/*  Patch::get_num_with_each_allele(std::vector<double> props, int n_alleles, int n_this_locus)
        Gets the number of individuals in the population with each allele, where props is a vector of the
        proportions of each allele.
*/
std::vector<int> Patch::get_num_with_each_allele(std::vector<double> props, int n_alleles, int n_this_locus){
    std::vector<int> num_per_allele;
    for (int i = 0; i < n_alleles; i++){
        num_per_allele.push_back(int(props[i]*n_this_locus));
    }

    int sum = 0;
    for (auto& n : num_per_allele)
        sum += n;

    int index;
    int resid = n_this_locus - sum;
    for (int i = 0; i < resid; i++){
        index = random_gen->uniform_int(0, n_alleles-1);
        num_per_allele[i]++;
    }
    return num_per_allele;
}

/*  Patch::gen_alleles(int n_alleles)
        Generates n_alleles allele values from a uniform distribution over [0.0, 1.0]
*/
std::vector<double> Patch::gen_alleles(int n_alleles){
    std::vector<double> alleles;
    for (int i = 0; i < n_alleles; i++){
        alleles.push_back(random_gen->uniform_float(0.0, 1.0));
    }
    return alleles;
}

// ==========================================
// Core Methods
// ==========================================
    // Each of these methods are called once per generation

/*  Patch::migrate()
        Gets the set of patches that an indvidual can migrate to, and then calls
        migrate() on the individual level where preference values are calculated
*/
void Patch::migrate(){
    std::vector<Patch*> surrounding_patches = this->get_surrounding_patches();
    std::vector<Individual*> indivs = this->get_all_individuals();

    for (Individual* indiv : indivs){
      indiv->migrate(surrounding_patches);
    }
}

/*  Patch::selection()
        Calculates fitness for each individual in the patch, and then calls
        the individual selection() function where relative fitness is used to determine
        if an indvidual survives or not.
*/
void Patch::selection(){
    std::vector<Individual*> indivs = this->get_all_individuals();
    double w;
    bool surv;

    for (Individual* indiv : indivs){
        w = indiv->calc_fitness();
        if (w > this->max_fitness){
            this->max_fitness = w;
        }
    }

    for (Individual* indiv : indivs){
        surv = indiv->selection(this->max_fitness);
        if (!surv){
            this->remove_individual(indiv);
            delete indiv;
        }
    }

    this->set_max_fitness(0.0);
}

/*  Patch::mating()
        Random mating among individuals in the patch who survived selection.
*/
void Patch::mating(){

    std::vector<Individual*> indivs = this->get_all_individuals();

    std::vector<Individual*> males;
    std::vector<Individual*> females;

    for (Individual* indiv : indivs){
        if (indiv->get_sex() == MALE){
            males.push_back(indiv);
        }
        else if (indiv->get_sex() == FEMALE){
            females.push_back(indiv);
        }
    }

    if (males.size() < 1 || females.size() < 1){
        return;
    }

    if (males.size() + females.size() < 2){
        return;
    }

    int rand_index, n_offspring, sex;
    Individual *male, *offspring;
    double *haplo0, *haplo1;
    bool parent_is_migrant;

    for (Individual* female: females){
        parent_is_migrant = false;
        rand_index = random_gen->uniform_int(0, males.size()-1);
        male = males[rand_index];

        if (female->is_migrant() || male->is_migrant()){
            parent_is_migrant = true;
        }

        n_offspring = random_gen->n_offspring();

        for (int i = 0; i < n_offspring; i++){
            haplo0 = female->make_gamete();
            haplo1 = male->make_gamete();

            // coin flip to determine sex
            if (random_gen->uniform_int(0,1) == 0){
                sex = MALE;
            }
            else{
                sex = FEMALE;
            }

            offspring = new Individual(this, sex, parent_is_migrant);
            offspring->set_haplotype(0, haplo0);
            offspring->set_haplotype(1, haplo1);
            this->add_offspring(offspring);
        }
    }

    this->replace_old_gen();
}

/*  Patch::census_patch()
        Censuses all individuals in the patch.
*/
void Patch::census_patch(){
    std::vector<Individual*> indivs = this->get_all_individuals();
    for (Individual* indiv : indivs){
        indiv->census_indiv();
    }

    for (Individual* indiv : indivs){
        indiv->census_dependent_alleles();
    }
}

// ==========================================
// Utility functions
// ==========================================

/*  Patch::add_individual(Individual* indiv)
        Add the Individual* indiv to the hashtable of indviduals in the patch
*/
void Patch::add_individual(Individual* indiv){
    std::pair<int, Individual*> value(indiv->get_id(), indiv);
    this->indivs->insert(value);
    this->n_indiv++;
}

/*  Patch::remove_individual(Individual* indiv)
        Removes the Individual* indiv from the hashtable of individuals in the patch.
*/
void Patch::remove_individual(Individual* indiv){
    this->indivs->erase(indiv->get_id());
    this->n_indiv--;
}

/*  Patch::mark_patch_fragmented()
        Marks this patch fragmented, thereby making it uninhabitable by indviduals.
*/
void Patch::mark_patch_fragmented(){
    this->fragmented = true;
    this->empty_patch();
}

/*  Patch::is_fragmented()
        Returns whether this patch is fragmented or not.
*/
bool Patch::is_fragmented(){
    return this->fragmented;
}

/*  Patch::add_offspring(Individual* offspring)
        Adds the Individual* offspring to the vector of next generation individuals.
*/
void Patch::add_offspring(Individual* offspring){
    std::pair<int, Individual*> value(offspring->get_id(), offspring);
    this->next_gen->insert(value);
}

/*  Patch::calc_effective_migration_rate()
        Calculates the effective migration rate of indviduals in the patch.
*/
double Patch::calc_effective_migration_rate(){
    std::vector<Individual*> indivs = this->get_all_individuals();
    int ct = 0;
    for (Individual* in : indivs){
        if (in->is_parent_migrant()){
            ct++;
        }
    }

    return double(ct)/double(this->get_n_indiv());
}

/*  Patch::empty_patch()
        Delete all of the Indivduals in the hashtable of indivduals in the patch
*/
void Patch::empty_patch(){
    std::vector<Individual*> old_gen = this->get_all_individuals();
    for (Individual* indiv: old_gen){
        this->remove_individual(indiv);
        delete indiv;
    }

    #if __DEBUG__

    #endif
}

/*  Patch::replace_old_gen()
        Replaces the current generation of indivduals with the vector of Indivduals next_gen
*/
void Patch::replace_old_gen(){
    this->empty_patch();
    delete this->indivs;
    this->indivs = this->next_gen;

    this->next_gen = new std::unordered_map<int, Individual*>;
}

// ===============================================
// Setters and Getters
// ===============================================

std::vector<Patch*> Patch::get_surrounding_patches(){
    return this->board->get_surrounding_patches(this->x, this->y);
}

std::vector<Individual*> Patch::get_all_individuals(){
    int ct = this->indivs->size();

    std::vector<Individual*> individuals;

    if (ct < 1){
        return individuals;
    }

    Individual* tmp_indiv;
    for (auto ind: *this->indivs){
        tmp_indiv = ind.second;
        individuals.push_back(tmp_indiv);
    }

    return individuals;
}

void Patch::set_max_fitness(double fitness){
    this->max_fitness = fitness;
}
double Patch::get_max_fitness(){
    return this->max_fitness;
}

double Patch::get_envFactor_value(int envFactor){
    return this->envFactor_values[envFactor];
}

int Patch::get_x(){
    return this->x;
}

int Patch::get_y(){
    return this->y;
}

int Patch::get_n_indiv(){
    return this->indivs->size();
}
