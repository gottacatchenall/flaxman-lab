#include "include.h"
#include "cmd_line_opts.h"
#include "genetic_map.h"
#include "params_struct.h"
#include "Logger.h"
#include "Board.h"
#include "Random.h"
#include "Fractal.h"
#include "GeneTracker.h"
#include "TimeTracker.h"

#include <string>

// Globals
TimeTracker* time_tracker;
genetic_map_s* genetic_map;
Random* random_gen;
params_s* params;
Logger* logger;
Fractal* fractal;
GeneTracker* gene_tracker;

int main(int argc, char* argv[]){

    time_tracker = new TimeTracker();

    // Setup custom parameters
    params = new params_s;
    get_options(argc, argv, params);

    gene_tracker = new GeneTracker();

    #if __DEBUG__
        printf("Running in __DEBUG__ mode! This enables inline unit testing/validation, but will *significantly* slow performance. Running mpfm in this mode is discouraged unless you are debugging!\n\n");
    #endif

    // Setup Random Generator...
    random_gen = new Random(params->RANDOM_SEED_VALUE);

    // Setup Genetic Map...
    genetic_map = generate_genetic_map();

    // Setup Data Logger...
    int path_buffer_size = 1000;
    char dir_name[path_buffer_size];
    get_execuable_path(dir_name, path_buffer_size);
    logger = new Logger(std::string(dir_name));

    // Setup Fractal Gen
    fractal = new Fractal();

    // Board initialization
    Board* board = new Board();
    board->allocate_individuals();
    board->setup_initial_alleles();

    printf("\n");

    int gen;
    int n_gen = params->N_GENERATIONS;


    int frag_lo = params->FRAGMENTATION_START;
    int frag_hi = params->FRAGMENTATION_END;
    int log_freq = params->LOG_FREQUENCY;

    for (gen = 0; gen < n_gen+1; gen++){
        board->migrate();
        board->selection();

        if (gen % log_freq == 0){
            board->census_pop(gen);
        }

        board->mating();

        if (gen > frag_lo && gen < frag_hi){
            board->next_gen(gen);
        }

        // Print gen to console
        if (gen % 10 == 0){
            printf("\t=== Generation: [%d / %d] === \r", gen, n_gen);
            std::cout.flush();
        }
    }

    time_tracker->print_times();
    return 0;
}
