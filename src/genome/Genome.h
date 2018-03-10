
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
        int N_BEANBAG_CHROMO;
        int N_BEANBAG_LOCI_PER_CHROMO;

        int*** beanbag_loci;
        int* preferences;
        int* fitness;
        int* male_chromosome;
        int* female_chromosome;
    public:
        Genome(Individual* individual, Random* random, params_s* params);
        Genome* mate(Genome* mate_genome);
        void crossing_over(Genome* a, Genome* b, Genome* result);
};

#endif
