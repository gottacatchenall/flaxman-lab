
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "include.h"

class Individual{
    private:
        static int id_counter;
        int id;
        int sex;
        Patch* patch;

        bool parent_migrated;
        bool migrated;

        double w;
        double* haplotype0;
        double* haplotype1;
    public:
        Individual(Patch* patch, int sex, bool parent_is_migrant);
        ~Individual();

        // Core methods
            // These are called once per generation
        void migrate(std::vector<Patch*> surrounding_patches);
        bool selection(double max_fit);
        void census_indiv();
        void census_dependent_alleles();

        // Miscellaneous Utility Methods
        double fitness_gaussian(double diff);
        double beverton_holt_prob(double k_prime);
        double calc_fitness();
        double calc_pref(Patch* patch);

        double* make_gamete();
        double* crossing_over();

        void set_haplotype(int haplo_num, double* haplotype);

        // Getters and Setters
        int get_id();
        int get_sex();
        double get_allele(int locus, int haplo);
        void set_allele(int locus, double value, int haplo);
        bool is_migrant();
        bool is_parent_migrant();
};

#endif
