#include "Patch.h"
#include "Board.h"
#include "Individual.h"
#include "Random.h"
#include "bio_functions.h"
#include "params_struct.h"
#include <algorithm>

Patch::Patch(Board *board, int x, int y){
    this->n_indiv = 0;
    this->x = x;
    this->y = y;
    this->board = board;

    for (int i = 0; i < params->N_ENV_FACTORS; i++){
        this->envFactor_values.push_back(this->board->get_envFactor_value(this->x, this->y, i));
    }
}

// ==========================================
// Migration
// ==========================================

void Patch::migrate(){
    std::vector<Patch*> surrounding_patches = this->get_surrounding_patches();
    std::vector<Individual*> indivs = this->get_all_individuals();

    for (Individual* indiv : indivs){
        indiv->migrate(surrounding_patches);
    }
}

std::vector<Patch*> Patch::get_surrounding_patches(){
    return this->board->get_surrounding_patches(this->x, this->y);
}

// ==========================================
// Setup initial population
// ==========================================
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

std::vector<double> Patch::gen_alleles(int n_alleles){
    std::vector<double> alleles;
    for (int i = 0; i < n_alleles; i++){
        alleles.push_back(random_gen->uniform_float(0.0, 1.0));
    }
    return alleles;
}

void Patch::setup_initial_alleles(){
    int N_LOCI = params->N_LOCI;
    std::vector<Individual*> indiv = this->get_all_individuals();

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
            indiv[i]->set_allele(locus, allele_map[allele_ct], 1);
            allele_ct++;
            indiv[i]->set_allele(locus, allele_map[allele_ct], 2);
            allele_ct++;
        }
    }
}

// ==========================================
// Utility functions
// ==========================================

int Patch::get_x(){
    return this->x;
}

int Patch::get_y(){
    return this->y;
}

int Patch::get_envFactor_value(int envFactor){
    return this->envFactor_values[envFactor];
}

void Patch::add_individual(Individual* indiv){
    std::pair<int, Individual*> value(indiv->get_id(), indiv);
    this->indivs.insert(value);
    this->increment_num_indiv();
}

void Patch::remove_individual(Individual* indiv){
    this->indivs.erase(indiv->get_id());
    this->decrement_num_indiv();
}

int Patch::get_n_indiv(){
    return this->n_indiv;
}

std::vector<Individual*> Patch::get_all_individuals(){
    int ct = this->indivs.size();

    std::vector<Individual*> individuals;

    if (ct < 1){
        return individuals;
    }

    Individual* tmp_indiv;
    for (auto ind: this->indivs){
        tmp_indiv = ind.second;
        individuals.push_back(tmp_indiv);
    }

    return individuals;
}

void Patch::increment_num_indiv(){
    this->n_indiv++;
}

void Patch::decrement_num_indiv(){
    this->n_indiv--;
}
