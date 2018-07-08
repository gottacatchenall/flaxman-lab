
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "include.h"

class Individual{
    private:
        static int id_counter;
        int id;
        int sex;
        Patch* patch;

        double w;
        double* haplotype0;
        double* haplotype1;
    public:
        Individual(Patch* patch, int sex);
        ~Individual();
        int get_id();
        int get_sex();
        void migrate(std::vector<Patch*> surrounding_patches);
        double fitness_gaussian(double diff);
        double beverton_holt_prob(double k_prime);
        double calc_fitness();
        bool selection(double max_fit);

        double calc_pref(Patch* patch);
        void choose_mate();
        void set_allele(int locus, double value, int haplo);
        double get_allele(int locus, int haplo);


        double* make_gamete();
        double* crossing_over();

        void set_haplotype(int haplo_num, double* haplotype);
        void reproduce(Individual* mate);

        void census_indiv();
        void census_dependent_alleles();

};

#endif
