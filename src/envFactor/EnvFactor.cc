
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
    if (params->BINARY_ENV_FACTORS){
        int** map = fractal->create_binary_map_from_fractal(fractal->generate_fractal(this->H_VALUE), 0.5);

        int n = this->BOARD_SIZE;
        double** grid = new double*[n];
        for (int i = 0; i < n; i++){
            grid[i] = new double[n];
        }


        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                grid[i][j] = double(map[i][j]);
            }
        }

        this->envFactor_grid = grid;
    }
    else{
        this->envFactor_grid = fractal->generate_fractal(this->H_VALUE);
    }


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
