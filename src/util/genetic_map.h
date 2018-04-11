
#ifndef GENETIC_MAP_H
#define GENETIC_MAP_H

#include "include.h"
#include <vector>


// Genetic Map Struct
typedef struct genetic_map_s{
    std::vector<int> chromo_map;
    std::vector<int> pref_loci;
    std::vector<int> fitness_loci;
    int m_locus;
    int f_locus;
    int c_locus;
} genetic_map_s;

genetic_map_s* generate_genetic_map();
int* generate_perm_with_uniq_ints(int size, int n);


#endif
