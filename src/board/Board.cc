
#include "Board.h"
#include "Patch.h"
#include "EnvFactor.h"
#include "Random.h"
#include "Logger.h"
#include "Fractal.h"
#include "Individual.h"
#include "Fragment.h"
#include "params_struct.h"

Board::Board (Random* random, Fractal* fractal, Logger* logger, params_s* params, genetic_map_s* genetic_map){
    assert(random != NULL);
    assert(fractal != NULL);
    assert(logger != NULL);
    assert(params != NULL);
    assert(genetic_map != NULL);
    assert(params->BOARD_SIZE > 0 && "board size must be greater than 0!");
    assert(params->N_ENV_FACTORS > 0 && "the number of environmental factors must be greater than 0!");


    this->params = params;
    this->BOARD_SIZE = params->BOARD_SIZE;
    this->N_ENV_FACTORS = params->N_ENV_FACTORS;
    this->random = random;
    this->fractal = fractal;
    this->logger = logger;
    this->genetic_map = genetic_map;

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
            this->grid[i][j] = new Patch(this, this->params, this->random, x, y);
        }
    }

    // =======================================
    // Fragment Map Initialization
    // =======================================
    this->fragment = new Fragment(this->random, this->fractal, this->logger, params);
    logger->write_fragment_map(this->fragment);

    #if __DEBUG__
        // Check that Fragment map cover amount is between the supplied parameters
    #endif
}

Patch* Board::get_patch(int x, int y){
    // Remember, this->grid is padded by NULLs on all sides,
    // so, index must be adjusted so (x,y) actually maps to (x,y)
    int i = x + 1;
    int j = y + 1;

    return this->grid[i][j];
}

bool Board::on_board(int x, int y){
    if (x < 0 || x >= this->BOARD_SIZE || y < 0 || y >= this->BOARD_SIZE){
        return false;
    }
    return true;
}


std::vector<Patch*> Board::get_surrounding_patches(int x, int y){
    int migration_dist = this->params->MIGRATION_DISTANCE;
    std::vector<Patch*> surrounding_patches;

    for (int i = -1*migration_dist; i <= migration_dist; i++){
        for (int j = -1*migration_dist; j <= migration_dist; j++){
            if (this->on_board(x+i, y+j)){
                surrounding_patches.push_back(this->get_patch(x+i, y+j));
            }
        }
    }

    return surrounding_patches;
}

int Board::get_envFactor_value(int x, int y, int envFactor){
    return this->envFactors[envFactor]->get_cell_value(x,y);
}

void Board::allocate_individuals(){

    // Pick locations of patches that will be initially occupied
    int n_patches = this->params->N_MAX_INIT_OCCUPIED_PATCHES;
    int x[n_patches];
    int y[n_patches];

    for (int i = 0; i < n_patches; i++){
        x[i] = this->random->uniform_int(0, this->BOARD_SIZE-1);
        y[i] = this->random->uniform_int(0, this->BOARD_SIZE-1);
    }

    // Put individuals in these patches
    int n_indiv = this->params->N_INDIVIDUALS;
    int random_index, hash_key;
    for (int i = 0; i < n_indiv; i++){
        random_index = this->random->uniform_int(0, n_patches-1);
        Patch* patch = this->get_patch(x[random_index], y[random_index]);

        Individual* indiv = new Individual(patch, this->random, this->params, this->genetic_map);

        patch->add_individual(indiv);
        hash_key = std::stoi(std::to_string(patch->get_x()) + ',' + std::to_string(patch->get_y()));
        if (this->occupied_patches.find(hash_key) == this->occupied_patches.end()){
            // Not yet in occupied patches hashtable
            this->occupied_patches.insert(std::pair<int, Patch*>(hash_key, patch));
        }
    }
}

void Board::setup_initial_alleles(){
    Patch* patch;
    for (auto pair: this->occupied_patches){
        patch = pair.second;
        patch->setup_initial_alleles();
    }
}

void Board::log_gen(int gen){
    // get all indivs and log
    //bool write_data = !(gen % 300);
    bool write_data = true;
    Patch* patch;
    if (write_data){
        std::vector<std::vector<int>> map(this->BOARD_SIZE,std::vector<int>(this->BOARD_SIZE));
        for (int i = 0; i < this->BOARD_SIZE; i++){
            for (int j = 0; j < this->BOARD_SIZE; j++){
                patch = this->get_patch(i,j);
                map[i][j] = patch->get_n_indiv();
            }
        }

        this->logger->write_generation_data(gen, map);

    }
}


void Board::migrate(){
    Patch* patch;
    for (auto obj: this->occupied_patches){
        patch = obj.second;
        patch->migrate();
    }

    occupied_patches.clear();

    int hash_key;

    // TODO this could be better
    for (int i = 0; i < this->BOARD_SIZE; i++){
        for (int j = 0; j < this->BOARD_SIZE; j++){
            patch = this->get_patch(i,j);
            if (patch->get_n_indiv() > 0){
                hash_key = std::stoi(std::to_string(patch->get_x()) + ',' + std::to_string(patch->get_y()));
                if (this->occupied_patches.find(hash_key) == this->occupied_patches.end()){
                    // Not yet in occupied patches hashtable
                    this->occupied_patches.insert(std::pair<int, Patch*>(hash_key, patch));
                }
            }
        }
    }

}

void Board::next_gen(int gen){
    this->fragment->fragment_more(gen);
}
