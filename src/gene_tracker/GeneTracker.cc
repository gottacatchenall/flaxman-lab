#include "GeneTracker.h"
#include "params_struct.h"

GeneTracker::GeneTracker(){
    int n_loci = params->N_LOCI;
    this->allele_map = new std::vector<allele*>[n_loci];
}

allele* GeneTracker::find_allele(int locus, double allele_val){
    std::vector<allele*> allele_vec = this->allele_map[locus];

    for(allele* al: allele_vec) {
        if (al->allele_val == allele_val){
            return al;
        }
    }
    return NULL;
}

void GeneTracker::add_dependent_allele(allele* primary_allele, int dependent_locus, double dependent_allele_val, int x, int y){
    assert(primary_allele != NULL);

    dependent_allele* dep_al;

    for (dependent_allele* al2 : primary_allele->loci[dependent_locus]){
        if (al2->allele_val == dependent_allele_val){
            dep_al = al2;
            dep_al->freq_map[x][y]++;
            dep_al->n_total++;
            return;
        }
    }


    dep_al = new dependent_allele(dependent_locus, dependent_allele_val);
    primary_allele->loci[dependent_locus].push_back(dep_al);

    dep_al->freq_map[x][y]++;
    dep_al->n_total++;
}

void GeneTracker::update_tracker(int locus, double allele_val, int x, int y){

    allele* allele_struct = this->find_allele(locus, allele_val);
    if (allele_struct != NULL){
        allele_struct->n_total++;
        allele_struct->freq_map[x][y]++;
    }
    else{
        allele* new_allele = new allele(locus, allele_val);
        new_allele->n_total++;
        new_allele->freq_map[x][y]++;
        this->allele_map[locus].push_back(new_allele);
    }
}

std::vector<allele*> GeneTracker::get_locus_vector(int locus){
    return this->allele_map[locus];
}

void GeneTracker::erase_data(){
    int n_loci = params->N_LOCI;
    std::vector<allele*> allele_vec;
    int N = params->BOARD_SIZE;

    for (int l1 = 0; l1 < n_loci; l1++){
        allele_vec = this->allele_map[l1];
        for(allele* al: allele_vec) {
            for (int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                    al->freq_map[i][j] = 0;
                }
            }

            al->n_total = 0;

        /*    for (int l2 = l1+1; l2 < n_loci; l2++ ){
                for (dependent_allele* al2: al->loci[l2]){
                    delete al2;
                }
            }*/

            for (int l2 = l1+1; l2 < n_loci; l2++ ){
                for (dependent_allele* al2: al->loci[l2]){
                    al2->n_total = 0;
                    for (int i = 0; i < N; i++){
                        for (int j = 0; j < N; j++){
                            al2->freq_map[i][j] = 0;
                        }
                    }
                }
            }
            //delete al;
        }
    }

}
