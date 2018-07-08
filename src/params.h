
// -----------------------------------
// Board
// -----------------------------------

#define BOARD_SIZE_DEFAULT 8
#define N_ENV_FACTORS_DEFAULT 8
#define N_GENERATIONS_DEFAULT 10000
#define RANDOM_SEED_VALUE_DEFAULT time(NULL)

#define CARRYING_CAPACITY_DEFAULT 300

// -----------------------------------
// Environmental Factors
// -----------------------------------

#define ENV_FACTOR_H_VALUE_DEFAULT .8
#define ENV_FACTOR_CUTOFF_DEFAULT 0.1

// -----------------------------------
// Fragmentation
// -----------------------------------

#define FRAGMENT_AMOUNT_LOW_DEFAULT 0.45
#define FRAGMENT_AMOUNT_HI_DEFAULT 0.65
#define FRAGMENT_H_VALUE_DEFAULT 0.1
#define FRAGMENT_PROBABILITY_DEFAULT 0.05

// -----------------------------------
// Individuals
// -----------------------------------

#define N_INDIVIDUALS_DEFAULT 300
#define INDIVIDUALS_INITIAL_GENOME_DEFAULT INDIVIDUALS_RANDOM_GENOTYPE
#define N_MAX_INIT_OCCUPIED_PATCHES_DEFAULT 5
#define MIGRATION_DISTANCE_DEFAULT 1
#define MIGRATION_TENDENCY_DEFAULT 0.5

#define SELECTION_STRENGTH_DEFAULT 0.1
#define AVG_NUM_OFFSPRING_PER_FEMALE_DEFAULT 3

// -----------------------------------
// Genome
// -----------------------------------

#define LINKAGE_MODE_DEFAULT NORMAL_LINKAGE

#define N_CHROMOSOMES_DEFAULT 5
#define N_LOCI_DEFAULT 80
#define MUTATION_RATE_DEFAULT 0.0001 // 10^-5

#define GENOME_LENGTH_IN_CENTIMORGANS_DEFAULT 3
