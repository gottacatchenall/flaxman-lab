
#include "Board.h"
#include "Patch.h"
#include "EnvFactor.h"
#include "Random.h"
#include "Logger.h"
#include "Fractal.h"
#include "Fragment.h"
#include "params_struct.h"

Board::Board (Random* random, Fractal* fractal, Logger* logger, params_s* params){
    assert(random != NULL);
    assert(fractal != NULL);
    assert(logger != NULL);
    assert(params != NULL);
    assert(params->BOARD_SIZE > 0);
    assert(params->N_ENV_FACTORS > 0);


    this->BOARD_SIZE = params->BOARD_SIZE;
    this->N_ENV_FACTORS = params->N_ENV_FACTORS;
    this->random = random;
    this->fractal = fractal;
    this->logger = logger;

    // =======================================
    // Grid Initialization
    // =======================================

    // Initiallize Grid 2D-Array

    // Size is BOARD_SIZE+2 so entire thing is surrounded by NULLs to avoid
    // issues with indexing surrounding patches at edges or corner.

    this->grid = new Patch**[this->BOARD_SIZE+2];
    for (int i = 0; i < this->BOARD_SIZE+2; i++) {
        this->grid[i] = new Patch*[this->BOARD_SIZE+2];
    }

    // Initialize Edges to NULL
    int max_index = this->BOARD_SIZE+1;
    for (int i = 0; i < this->BOARD_SIZE+2; i++){
        this->grid[i][0] = NULL;
        this->grid[i][max_index] = NULL;
        this->grid[0][i] = NULL;
        this->grid[max_index][i] = NULL;
    }

    // Initiallize Patch
    int x,y;
    for (int i = 1; i < this->BOARD_SIZE+1; i++){
        for (int j = 1; j < this->BOARD_SIZE+1; j++){
            // adjust indecies to pass to patch as coordinate
            x = i - 1;
            y = j - 1;
            this->grid[i][j] = new Patch(x, y, this);
        }
    }

    // =======================================
    // EnvFactor Initialization
    // =======================================
    this->envFactors = new EnvFactor*[this->N_ENV_FACTORS];
    for (int i = 0; i < this->N_ENV_FACTORS; i++){
        this->envFactors[i] = new EnvFactor(this->random, this->fractal, params, i);
    }

    // Write EnvFactor
    for (int i = 0; i < this->N_ENV_FACTORS; i++){
        logger->write_envFactor(this->envFactors[i]);
    }


    // =======================================
    // Fragment Map Initialization
    // =======================================
    this->fragment = new Fragment(this->random, this->fractal, this->logger, params);
    logger->write_fragment_map(this->fragment);

#if __DEBUG__
    // Check that Fragment map cover amount is between the supplied parameters
#endif

    // =======================================
    // Genome Map Initialization
    // =======================================

}

Patch* Board::get_patch(int x, int y){
    // Remember, this->grid is padded by NULLs on all sides,
    // so, index must be adjusted so (x,y) actually maps to (x,y)
    int i = x + 1;
    int j = y + 1;

    return this->grid[i][j];
}

void Board::allocate_individuals(){
    // TODO
}

void Board::migrate(){
    // TODO
}

void Board::next_gen(int gen){
    this->fragment->fragment_more(gen);
}
