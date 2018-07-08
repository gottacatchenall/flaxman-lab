#ifndef GENETRACKER_H
#define GENETRACKER_H

#include "include.h"
#include "params_struct.h"
#include <vector>

typedef struct dependent_allele{
    dependent_allele(int l, double val){
        locus = l;
        allele_val = val;
        n_total = 0;

        freq_map = new int*[params->BOARD_SIZE];
        for (int i = 0; i < params->BOARD_SIZE; i++){
            freq_map[i] = new int[params->BOARD_SIZE];
            for (int j = 0; j < params->BOARD_SIZE; j++){
                freq_map[i][j] = 0;
            }
        }

    };

    ~dependent_allele(){
        for (int i = 0; i < params->BOARD_SIZE; i++){
            delete freq_map[i];
        }
        delete freq_map;
    }

    int locus;
    double allele_val;
    int n_total;
    int** freq_map;
} dependent_allele;

typedef struct allele{

    allele(int l, double val){
        locus = l;
        allele_val = val;
        n_total = 0;

        loci = new std::vector<dependent_allele*>[params->N_LOCI];

        freq_map = new int*[params->BOARD_SIZE];
        for (int i = 0; i < params->BOARD_SIZE; i++){
            freq_map[i] = new int[params->BOARD_SIZE];
            for (int j = 0; j < params->BOARD_SIZE; j++){
                freq_map[i][j] = 0;
            }
        }

    };

    ~allele(){
        for (int i = 0; i < params->BOARD_SIZE; i++){
            delete freq_map[i];
        }
        delete freq_map;

        delete loci;
    }

    int locus;
    double allele_val;
    int n_total;
    int** freq_map;
    std::vector<dependent_allele*>* loci;
} allele;

class GeneTracker{
    private:
        std::vector<allele*>* allele_map;
    public:
        GeneTracker();
        void add_dependent_allele(allele* primary_allele, int dependent_locus, double dependent_allele_val, int x, int y);
        void update_tracker(int locus, double allele_val, int x, int y);
        std::vector<allele*> get_locus_vector(int locus);
        void erase_data();
        allele* find_allele(int locus, double allele_val);
};

#endif
