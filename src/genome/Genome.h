
#ifndef GENOME_H
#define GENOME_H

#include "include.h"

class Random;
class Individual;

class Genome{
    private:
      Individual *individual;
      Random* random;
      int* preferences;
      int* fitness;
      int* male_chromosome;
      int* female_chromosome;
    public:
      Genome(Individual* individual, Random* random);
      Genome* mate(Genome* mate_genome);
      void crossing_over(Genome* a, Genome* b, Genome* result);
};

#endif
