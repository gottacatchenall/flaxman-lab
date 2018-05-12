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

void GeneTracker::update_tracker(int locus, double allele_val, int x, int y){

    // TODO
        // init doesn't set all alleles to non-zero value?
            // every other allele?  
        // something in erase data causes it to seg fault
        // maybe don't erase and reset nums each census. lets you track lost alleles
    allele* allele_struct = this->find_allele(locus, allele_val);
    if (allele_struct != NULL){
        allele_struct->n_observed_total++;
        allele_struct->freq_map[x][y]++;
    }
    else{
        allele* new_allele = new allele(locus, allele_val);
        new_allele->n_observed_total++;
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

    for (int locus = 0; locus < n_loci; locus++){
        allele_vec = this->allele_map[locus];
        for(allele* al: allele_vec) {
            // reset freq_map
            for (int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                    al->freq_map[i][j] = 0;
                }
            }

            al->n_observed_total = 0;
        }
    }
}
