
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "include.h"

class Genome;
class Random;
struct params_s;
typedef params_s params_s;

class Individual{
    private:
        static int id_counter;
        int id;
        Random *random;
        Genome *genome;
        params_s *params;
    public:
        Individual(Random *random, params_s* params);
        void get_initial_alleles();
        void migrate();
        void get_fitness();
        void choose_mate();
        void reproduce(Individual* mate);
};

#endif
