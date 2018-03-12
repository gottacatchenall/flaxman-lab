#include "include.h"
#include "cmd_line_opts.h"
#include "genetic_map.h"
#include "params_struct.h"
#include "Logger.h"
#include "Board.h"
#include "Random.h"
#include "Fractal.h"

#include <string>

int main(int argc, char* argv[]){


    // Setup custom parameters
    params_s* params = new params_s;
    get_options(argc, argv, params);

#if __DEBUG__
    printf("Running in __DEBUG__ mode! This enables inline unit testing/validation, but will significantly slow performance.\n\n");
#endif

    // Setup Random Generator...
    int random_seed = RANDOM_SEED_VALUE;
    Random* random = new Random(random_seed);

    // Setup Genetic Map...
    genetic_map_s* genetic_map = generate_genetic_map(random, params);

    // Setup Data Logger...
    int path_buffer_size = 200;
    char dir_name[path_buffer_size];
    get_execuable_path(dir_name, path_buffer_size);
    std::string dir_name_str(dir_name);
    Logger* logger = new Logger(dir_name_str, params);

    // Setup Fractal Gen
    Fractal* fractal = new Fractal(random, params);

    // Board initialization
    Board* board = new Board(random, fractal, logger, params, genetic_map);
    board->allocate_individuals();

    int i;
    int n_gen = params->N_GENERATIONS;
    for (i = 0; i < n_gen; i++){
        board->migrate();
        board->next_gen(i);
    }

    return 0;
}
