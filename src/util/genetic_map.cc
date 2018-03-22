
#include "genetic_map.h"
#include "params_struct.h"
#include "Random.h"

genetic_map_s* generate_genetic_map(){
    genetic_map_s* map = new genetic_map_s;


    map->chromo_map = generate_perm_with_uniq_ints(params->N_CHROMOSOMES, params->N_LOCI);
    map->pref_loci = new int[params->N_ENV_FACTORS];
    map->fitness_loci = new int[params->N_ENV_FACTORS];
    map->male_loci = new int[2];
    map->female_loci = new int[1];

    int n_unique_indecies = params->N_ENV_FACTORS + params->N_ENV_FACTORS + 2 + 1;
    int* uniq_perm = generate_perm_with_uniq_ints(n_unique_indecies, params->N_LOCI);

    int pref_offset = 0;
    int fitness_offset = params->N_ENV_FACTORS;
    int male_offset = 2*params->N_ENV_FACTORS;
    int female_offset = 2*params->N_ENV_FACTORS + 2;

    for (int i = 0; i < n_unique_indecies; i++){
        if (i < fitness_offset){
            map->pref_loci[i+pref_offset] = uniq_perm[i];
        }
        else if(i >= fitness_offset && i < male_offset){
            map->fitness_loci[i-fitness_offset] = uniq_perm[i];
        }
        else if (i >= male_offset && i < female_offset){
            map->male_loci[i-male_offset] = uniq_perm[i];
        }
        else{
            map->female_loci[i-female_offset] = uniq_perm[i];
        }
    }

    free(uniq_perm);
    return map;
}


// Generates a permutation of length size of integers from 0...n
int* generate_perm_with_uniq_ints(int size, int n){
    int* result = new int[size];
    int r;
    int exists;
    for(int i = 0; i < size; i++){
        do{
            exists = 0;
            r = random_gen->uniform_int(0,n);
            for (int j = 0; i < j; j++){
                if (result[j] == r){
                    exists = 1;
                    break;
                }
            }
        } while(exists);
        result[i] = r;
    }
    return result;
}
