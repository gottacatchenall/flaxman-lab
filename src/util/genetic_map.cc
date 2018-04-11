
#include "genetic_map.h"
#include "params_struct.h"
#include "Random.h"

genetic_map_s* generate_genetic_map(){
    genetic_map_s* map = new genetic_map_s;


    int* chromo = generate_perm_with_uniq_ints(params->N_CHROMOSOMES, params->N_LOCI);

    for (int i = 0; i < params->N_CHROMOSOMES; i++){
        map->chromo_map.push_back(chromo[i]);
    }


    int n_unique_indecies = params->N_ENV_FACTORS + params->N_ENV_FACTORS + 2 + 1;
    int* uniq_perm = generate_perm_with_uniq_ints(n_unique_indecies, params->N_LOCI);

    int fitness_offset = params->N_ENV_FACTORS;
    int male_offset = 2*params->N_ENV_FACTORS;
    int female_offset = 2*params->N_ENV_FACTORS + 1;

    for (int i = 0; i < n_unique_indecies; i++){
        if (i < fitness_offset){
            map->pref_loci.push_back(uniq_perm[i]);
        }
        else if(i >= fitness_offset && i < male_offset){
            map->fitness_loci.push_back(uniq_perm[i]);
        }
        else if (i >= male_offset && i < female_offset){
            map->m_locus = uniq_perm[i];
        }
        else if (i < n_unique_indecies - 1){
            map->f_locus = uniq_perm[i];
            map->c_locus = uniq_perm[i+1];
            break;
        }
    }

    std::sort(map->chromo_map.begin(), map->chromo_map.end());
    std::sort(map->pref_loci.begin(), map->pref_loci.end());
    std::sort(map->fitness_loci.begin(), map->fitness_loci.end());


    assert(map->chromo_map.size() == params->N_CHROMOSOMES);
    assert(map->pref_loci.size() == params->N_ENV_FACTORS);
    assert(map->fitness_loci.size() == params->N_ENV_FACTORS);

    free(chromo);
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
