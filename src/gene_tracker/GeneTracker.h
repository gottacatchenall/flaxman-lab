#ifndef GENETRACKER_H
#define GENETRACKER_H

#include "include.h"
#include "params_struct.h"
#include <vector>

typedef struct allele{
    allele(int l, double val){
        locus = l;
        allele_val = val;

        freq_map = new int*[params->BOARD_SIZE];
        for (int i = 0; i < params->BOARD_SIZE; i++){
            freq_map[i] = new int[params->BOARD_SIZE];
        }

    };

    ~allele(){
        for (int i = 0; i < params->BOARD_SIZE; i++){
            delete freq_map[i];
        }
        delete freq_map;
    }

    int locus;
    double allele_val;
    int n_observed_total;
    int** freq_map;
} allele;


class GeneTracker{
    private:
        std::vector<allele*>* allele_map;
    public:
        GeneTracker();
        void update_tracker(int locus, double allele_val, int x, int y);
        std::vector<allele*> get_locus_vector(int locus);
        void erase_data();
        allele* find_allele(int locus, double allele_val);
};

#endif
