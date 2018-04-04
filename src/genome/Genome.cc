
#include "Genome.h"
#include "Random.h"
#include "params_struct.h"

Genome::Genome(Individual* individual){
    this->individual = individual;

    this->N_CHROMOSOMES = params->N_CHROMOSOMES;
    this->N_LOCI = params->N_LOCI;

    this->haplotype1 = new double[this->N_LOCI];
    this->haplotype2 = new double[this->N_LOCI];
}

Genome::~Genome(){
    free(this->haplotype1);
    free(this->haplotype2);
}

void Genome::set_haplotype(int haplo_num, double* haplotype){

    if (haplo_num == 1){
        free(this->haplotype1);
        this->haplotype1 = haplotype;
        return;
    }
    else if (haplo_num == 2){
        free(this->haplotype2);
        this->haplotype2 = haplotype;
        return;
    }

    assert(0 && "set_haplotype called with invalid haplo_num");
}


double* Genome::make_gamete(){

    double* gamete = new double[params->N_LOCI];

    if (params->LINKAGE_MODE == ALL_LOCI_INDEPENDENT){
        int n_loci = params->N_LOCI;
        int haplo;
        for (int i = 0; i < n_loci; i++){
            haplo = random_gen->uniform_int(0,1);
            gamete[i] = this->get_allele(i, haplo);
        }
        return gamete;
    }
    else if (params->LINKAGE_MODE == NORMAL_LINKAGE){
        return gamete;
    }

    assert(0 && "neither linkage mode was chosen");
}

void Genome::crossing_over(){

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
