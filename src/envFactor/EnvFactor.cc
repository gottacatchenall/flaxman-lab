
#include "EnvFactor.h"
#include "Fractal.h"
#include "params_struct.h"

EnvFactor::EnvFactor(int index){
    assert(params->ENV_FACTOR_H_VALUE > 0 && params->ENV_FACTOR_H_VALUE < 1);
    assert(index >= 0);

    this->id = index;
    this->BOARD_SIZE = params->BOARD_SIZE;
    this->H_VALUE = params->ENV_FACTOR_H_VALUE;
    this->CUTOFF = params->ENV_FACTOR_CUTOFF;

    // Generate the Theta Map
    this->envFactor_grid = fractal->generate_fractal(this->H_VALUE);

    #if __DEBUG__
        // Check that EnvFactor cover amount is between the supplied parameters
    #endif
}

double EnvFactor::get_cell_value(int x, int y){
    return this->envFactor_grid[x][y];
}

void EnvFactor::set_cell_value(int x, int y, int val){
    this->envFactor_grid[x][y] = val;
}

int EnvFactor::get_id(){
    return this->id;
}

int EnvFactor::get_board_size(){
    return this->BOARD_SIZE;
}
