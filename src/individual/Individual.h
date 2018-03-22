
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
        double calc_pref(Patch* patch);
        void get_fitness();
        void choose_mate();
        void set_allele(int locus, double value, int haplo);
        double get_allele(int locus, int haplo);
        void reproduce(Individual* mate);
};

#endif
