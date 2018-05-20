
#ifndef PATCH_H
#define PATCH_H

#include <unordered_map>
#include <vector>
#include "include.h"

class Patch{
    private:
        int x;
        int y;
        int n_indiv;

        Board* board;

        std::vector<int> envFactor_values;

        // HASHTABLE of individuals on the tile.
        // KEY is the individual's id
        std::unordered_map<int, Individual*>* indivs;

        std::unordered_map<int, Individual*>* next_gen;
        void increment_num_indiv();
        void decrement_num_indiv();
    public:
        Patch(Board *board, int x, int y);

        // Initialization
        void setup_initial_alleles();
        std::vector<double> generate_allele_freq_from_beta(int n_alleles);
        std::vector<int> get_num_with_each_allele(std::vector<double> props, int n_alleles, int n_this_locus);
        std::vector<double> gen_alleles(int n_alleles);

        // Core methods
            // These are each called once per generation
        void migrate();
        void selection();
        void census_patch();
        void mating();
        void replace_old_gen();

        // Miscellaneous utility methods
        std::vector<Patch*> get_surrounding_patches();
        void add_individual(Individual* indiv);
        void remove_individual(Individual* indiv);
        void add_offspring(Individual* offspring);
        std::vector<Individual*> get_all_individuals();
        void empty_patch();

        // Getters and Setters
        int get_x();
        int get_y();
        int get_envFactor_value(int envFactor);
        int get_n_indiv();
};

#endif
