
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "include.h"

class Genome;
class Random;
class Patch;
struct params_s;
typedef params_s params_s;
struct genetic_map_s;
typedef genetic_map_s genetic_map_s;

class Individual{
    private:
        static int id_counter;
        int id;
        Patch* patch;
        Random *random;
        Genome *genome;
        params_s *params;
        genetic_map_s* genetic_map;
    public:
        Individual(Patch* patch, Random *random, params_s* params, genetic_map_s* genetic_map);
        int get_id();
        void get_initial_alleles();
        void migrate();
        void get_fitness();
        void choose_mate();
        void reproduce(Individual* mate);
};

#endif
