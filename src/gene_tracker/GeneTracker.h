#ifndef GENETRACKER_H
#define GENETRACKER_H

#include "include.h"
#include <vector>

typedef struct allele{
    int locus;
    int allele_val;
    int n_observed_total;
    std::vector<std::vector<int>> freq_map;
} allele;


class GeneTracker{
    private:
        std::vector<allele*>* allele_map;
    public:
        GeneTracker();
        void update_tracker(int locus, double allele_val, int x, int y);
        allele* find_allele(int locus, double allele_val);
};

#endif
