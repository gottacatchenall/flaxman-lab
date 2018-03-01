#include "Board.h"
#include "cmd_line_opts.h"
#include "include.h"

#include <iostream>

int main(int argc, char* argv[]){

    //srand (time(NULL));

    params_s* params = new params_s;
    get_options(argc, argv, params);

    // Board initialization
    Board board(&board, params->BOARD_SIZE, params->N_ENV_FACTORS, params->ENV_FACTOR_MODE);

    board.init_envFactors();

    return 0;
}
