
#ifndef GENOME_H
#define GENOME_H

#include "include.h"

class Genome{
    private:
        Individual *individual;

        int N_CHROMOSOMES;
        int N_LOCI;

        double* haplotype1;
        double* haplotype2;
    public:
        Genome(Individual* individual);
        Genome* mate(Genome* mate_genome);
        double get_allele(int locus, int haplo);
        void set_allele(int locus, double val, int haplo);
        void crossing_over(Genome* a, Genome* result);
};

#endif
