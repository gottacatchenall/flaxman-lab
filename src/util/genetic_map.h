
#ifndef GENETIC_MAP_H
#define GENETIC_MAP_H

#include "include.h"
#include "params_struct.h"

class Random;

extern Random* random_gen;
extern params_s* params;

// Genetic Map Struct
typedef struct genetic_map_s{
    int* chromo_map;
    int* pref_loci;
    int* fitness_loci;
    int* male_loci;
    int* female_loci;
} genetic_map_s;

genetic_map_s* generate_genetic_map();
int* generate_perm_with_uniq_ints(int size, int n);


#endif
