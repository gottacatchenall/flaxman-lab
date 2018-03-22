#include "include.h"
#include "cmd_line_opts.h"
#include "genetic_map.h"
#include "params_struct.h"
#include "Logger.h"
#include "Board.h"
#include "Random.h"
#include "Fractal.h"
#include "TimeTracker.h"

#include <string>

// Globals
TimeTracker* time_tracker;
genetic_map_s* genetic_map;
Random* random_gen;
params_s* params;
Logger* logger;
Fractal* fractal;


int main(int argc, char* argv[]){

    time_tracker = new TimeTracker();

    // Setup custom parameters
    params = new params_s;
    get_options(argc, argv, params);

    #if __DEBUG__
        printf("Running in __DEBUG__ mode! This enables inline unit testing/validation, but will significantly slow performance.\n\n");
    #endif

    // Setup Random Generator...
    random_gen = new Random(params->RANDOM_SEED_VALUE);

    // Setup Genetic Map...
    genetic_map = generate_genetic_map();

    // Setup Data Logger...
    int path_buffer_size = 200;
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

    int i;
    int n_gen = params->N_GENERATIONS;
    for (i = 0; i < n_gen; i++){
        board->log_gen(i);
        board->migrate();
        board->next_gen(i);

        // Print gen to console
        if (i % 100 == 0){
            printf("\t=== Generation: [%d / %d] === \r", i, n_gen);
            std::cout.flush();
        }
    }

    time_tracker->print_times();
    return 0;
}
