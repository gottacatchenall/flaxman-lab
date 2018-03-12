
// -----------------------------------
// Board
// -----------------------------------

#define BOARD_SIZE_DEFAULT 8
#define N_ENV_FACTORS_DEFAULT 8
#define N_GENERATIONS_DEFAULT 3000
#define RANDOM_SEED_VALUE time(NULL)

// -----------------------------------
// Environmental Factors
// -----------------------------------

#define ENV_FACTOR_H_VALUE_DEFAULT .8
#define ENV_FACTOR_CUTOFF_DEFAULT 0.1


// -----------------------------------
// Fragmentation
// -----------------------------------

#define FRAGMENT_AMOUNT_LOW_DEFAULT 0.2
#define FRAGMENT_AMOUNT_HI_DEFAULT 0.3
#define FRAGMENT_H_VALUE_DEFAULT 0.1
#define FRAGMENT_PROBABILITY_DEFAULT 0.5

// -----------------------------------
// Individuals
// -----------------------------------

#define N_INDIVIDUALS_DEFAULT 1000
#define INDIVIDUALS_INITIAL_GENOME_DEFAULT INDIVIDUALS_PERFECTLY_ADAPTED_GENOTYPE
#define N_MAX_INIT_OCCUPIED_PATCHES_DEFAULT (BOARD_SIZE_DEFAULT*BOARD_SIZE_DEFAULT) / 4


// -----------------------------------
// Genome
// -----------------------------------

#define N_CHROMOSOMES_DEFAULT 10
#define N_LOCI_DEFAULT 1000
