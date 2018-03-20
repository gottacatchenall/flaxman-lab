
#include "Genome.h"
#include "params_struct.h"

Genome::Genome(Individual* individual, Random* random, params_s* params){
    this->individual = individual;
    this->random = random;
    this->params = params;

    this->N_CHROMOSOMES = params->N_CHROMOSOMES;
    this->N_LOCI = params->N_LOCI;


    this->haplotype1 = new double[this->N_LOCI];
    this->haplotype2 = new double[this->N_LOCI];

    for (int i = 0; i < this->N_LOCI; i++){
        this->haplotype1[i] = 0.0;
        this->haplotype2[i] = 0.0;
    }
}

double Genome::get_allele(int locus, int haplo){
    if (haplo == 1){
        return this->haplotype1[locus];
    }
    return this->haplotype2[locus];
}

void Genome::set_allele(int locus, double value, int haplo){
    if (haplo == 1){
        this->haplotype1[locus] = value;
    }
    else{
        this->haplotype2[locus] = value;
    }
}

Genome* Genome::mate(Genome* mate_genome){
    return mate_genome;
}

void Genome::crossing_over(Genome* a, Genome* result){

}
