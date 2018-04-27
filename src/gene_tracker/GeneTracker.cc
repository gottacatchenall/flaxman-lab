#include "GeneTracker.h"
#include "params_struct.h"

GeneTracker::GeneTracker(){
    this->allele_map = new std::vector<allele*>[params->N_LOCI];
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

    allele* allele_struct = this->find_allele(locus, allele_val);

    if (allele_struct){
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
