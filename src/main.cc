#include "include.h"
#include "cmd_line_opts.h"
#include "Logger.h"
#include "Board.h"
#include "Random.h"
#include "Fractal.h"

#include <string>

int main(int argc, char* argv[]){

    // Setup custom parameters
    params_s* params = new params_s;
    get_options(argc, argv, params);

    // Setup Random Generator...
    int random_seed = RANDOM_SEED_VALUE;
    Random random(random_seed);

    // Setup Data Logger...
    int path_buffer_size = 200;
    char dir_name[path_buffer_size];
    get_execuable_path(dir_name, path_buffer_size);
    std::string dir_name_str(dir_name);
    Logger logger(dir_name_str, params);

    // Setup Fractal Gen
    Fractal fractal(&random, params->BOARD_SIZE);

    // Board initialization
    Board board(&board, &random, &fractal, &logger, params->BOARD_SIZE, params->N_ENV_FACTORS);

    printf("\n");
    return 0;
}
