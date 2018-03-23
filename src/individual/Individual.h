
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "include.h"

class Individual{
    private:
        static int id_counter;
        int id;
        Patch* patch;
        Genome *genome;
    public:
        Individual(Patch* patch);
        int get_id();
        void migrate(std::vector<Patch*> surrounding_patches);
        double fitness_gaussian(double diff);
        double beverton_holt_prob(double k_prime);
        double calc_fitness();
        bool selection();

        double calc_pref(Patch* patch);
        void choose_mate();
        void set_allele(int locus, double value, int haplo);
        double get_allele(int locus, int haplo);
        void reproduce(Individual* mate);
};

#endif
