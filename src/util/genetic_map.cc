#include "genetic_map.h"
#include "params_struct.h"
#include "Random.h"

genetic_map_s* generate_genetic_map(){
    genetic_map_s* map = new genetic_map_s;

    int* chromo = generate_perm_with_uniq_ints(params->N_CHROMOSOMES, params->N_LOCI);

    for (int i = 0; i < params->N_CHROMOSOMES; i++){
        map->chromo_map.push_back(chromo[i]);
    }

    int n_ef = params->N_ENV_FACTORS;
    int n_loci_per_ef = params->N_LOCI_PER_ENV_FACTOR;
    int n_unique_indecies = 2*n_loci_per_ef*n_ef;
    int* uniq_perm = generate_perm_with_uniq_ints(n_unique_indecies, params->N_LOCI);

    int ind = 0;

    for (int i = 0; i < n_ef; i++){
        std::vector<int> tmp_vec;
        for (int j = 0; j < n_loci_per_ef; j++){
            tmp_vec.push_back(uniq_perm[ind]);
            ind++;
        }
        map->fitness_loci.push_back(tmp_vec);
    }

    for (int i = 0; i < n_ef; i++){
        std::vector<int> tmp_vec;
        for (int j = 0; j < n_loci_per_ef; j++){
            tmp_vec.push_back(uniq_perm[ind]);
            ind++;
        }
        map->pref_loci.push_back(tmp_vec);
    }

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
