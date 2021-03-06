
#include "bio_functions.h"
#include "include.h"
#include "Random.h"

int expected_num_neutral_alleles(int n_indiv, double mu){
    /*
        The expected number of alleles in a population of size 2N alleles,
        as given by Ewen's as the sum from i = 0 to i = 2N -1 of (theta)/(theta+i),
    */
    /*
    double theta = 4.0 * double(n_indiv) * mu;
    printf("theta %.2f\n", theta);
    float res = 0;
    for (int i = 0; i <  n_indiv-1; i++){
        res += float(theta)/float(theta+i);
    }
    return (int) res;
    */


    return random_gen->uniform_int(20,40);
}
