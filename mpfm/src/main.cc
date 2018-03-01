#include "Individual.h"
#include "Board.h"
#include "cmd_line_opts.h"

#include <iostream>

int main(int argc, char* argv[]){
    params_s* params = new params_s;
    get_options(argc, argv, params);

    Board board(params->BOARD_SIZE, params->N_ENV_FACTORS);
    Board* board_addr = &board;

    board.set_address(board_addr);
    board.init_cells();

    board.init_envFactors();

    return 0;
}
