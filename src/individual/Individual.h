
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "include.h"

class Genome;

class Individual{
    private:
        int id;
        Genome *genome;
    public:
        Individual();
        void get_initial_alleles();
        void migrate();
        void get_fitness();
        void choose_mate();
        void reproduce(Individual* mate);
};

#endif
