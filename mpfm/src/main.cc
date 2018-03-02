#include "include.h"
#include "cmd_line_opts.h"
#include "Logger.h"
#include "Board.h"


#include <iostream>

int main(int argc, char* argv[]){

    int random_seed = RANDOM_SEED_VALUE;
    params_s* params = new params_s;
    get_options(argc, argv, params);

    // Setup Data Logger...
    Logger logger;

    // Board initialization
    Board board(&board, params->BOARD_SIZE, params->N_ENV_FACTORS, params->ENV_FACTOR_MODE);

    board.init_envFactors();

    printf("\n");
    return 0;
}
