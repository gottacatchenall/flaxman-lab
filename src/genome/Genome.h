
#ifndef GENOME_H
#define GENOME_H

#include "include.h"

class Random;
class Individual;
struct params_s;
typedef params_s params_s;

class Genome{
    private:
        Individual *individual;
        Random* random;
        params_s *params;

        int K_VALUE;
        int N_CHROMOSOMES;
        int N_LOCI;

        int* genome;
        int* genetic_map;
        int* pref_loci;
        int* fitness_loci;
        int* male_loci;
        int* female_loci;
    public:
        Genome(Individual* individual, Random* random, params_s* params);
        Genome* mate(Genome* mate_genome);
        void crossing_over(Genome* a, Genome* b, Genome* result);
};

#endif
