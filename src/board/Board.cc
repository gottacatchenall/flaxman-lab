
#include "Board.h"
#include "Patch.h"
#include "EnvFactor.h"
#include "Random.h"
#include "Logger.h"
#include "Fractal.h"
#include "Individual.h"
#include "Fragment.h"
#include "TimeTracker.h"
#include "params_struct.h"

// ===============================================
// Board Constructor
// ===============================================

Board::Board (){
    assert(params->BOARD_SIZE > 0 && "board size must be greater than 0!");
    assert(params->N_ENV_FACTORS > 0 && "the number of environmental factors must be greater than 0!");

    double start_time = time_tracker->get_start_time();

    this->BOARD_SIZE = params->BOARD_SIZE;
    this->N_ENV_FACTORS = params->N_ENV_FACTORS;

    // =======================================
    // EnvFactor Initialization
    // =======================================
    this->envFactors = new EnvFactor*[this->N_ENV_FACTORS];
    for (int i = 0; i < this->N_ENV_FACTORS; i++){
        this->envFactors[i] = new EnvFactor(i);
    }

    // Write EnvFactor
    for (int i = 0; i < this->N_ENV_FACTORS; i++){
        logger->write_envFactor(this->envFactors[i]);
    }

    // =======================================
    // Grid Initialization
    // =======================================

    // Initiallize Grid 2D-Array
    this->grid = new Patch**[this->BOARD_SIZE];
    for (int i = 0; i < this->BOARD_SIZE; i++) {
        this->grid[i] = new Patch*[this->BOARD_SIZE];
    }

    // Initiallize Patches
    for (int i = 0; i < this->BOARD_SIZE; i++){
        for (int j = 0; j < this->BOARD_SIZE; j++){
            this->grid[i][j] = new Patch(this, i, j);
        }
    }

    // =======================================
    // Fragment Map Initialization
    // =======================================
    this->fragment = new Fragment();
    logger->write_fragment_map(this->fragment);

    #if __DEBUG__
        // Check that Fragment map cover amount is between the supplied parameters
    #endif

    time_tracker->add_time_in_setup(start_time);
}

// ===============================================
// Getters and Setters
// ===============================================

Patch* Board::get_patch(int x, int y){
    return this->grid[x][y];
}

std::vector<Patch*> Board::get_surrounding_patches(int x, int y){
    int migration_dist = params->MIGRATION_DISTANCE;
    std::vector<Patch*> surrounding_patches;

    for (int i = -1*migration_dist; i <= migration_dist; i++){
        for (int j = -1*migration_dist; j <= migration_dist; j++){
            if (!(i == 0 && j == 0) && this->on_board(x+i, y+j)){
                surrounding_patches.push_back(this->get_patch(x+i, y+j));
            }
        }
    }

    return surrounding_patches;
}

int Board::get_envFactor_value(int x, int y, int envFactor){
    return this->envFactors[envFactor]->get_cell_value(x,y);
}


bool Board::on_board(int x, int y){
    if (x < 0 || x >= this->BOARD_SIZE || y < 0 || y >= this->BOARD_SIZE){
        return false;
    }
    return true;
}

void Board::mark_patch_occupied(Patch* patch){
    int hash_key = (long int) patch;
    if (this->occupied_patches.find(hash_key) == this->occupied_patches.end()){
        this->occupied_patches.insert(std::pair<int, Patch*>(hash_key, patch));
    }
}

void Board::mark_patch_unoccupied(Patch* patch){
    int hash_key = (long int) patch;
    if (this->occupied_patches.find(hash_key) != this->occupied_patches.end()){
        this->occupied_patches.erase(hash_key);
    }
}

void Board::allocate_individuals(){

    // Pick locations of patches that will be initially occupied
    int n_patches = params->N_MAX_INIT_OCCUPIED_PATCHES;
    int x[n_patches];
    int y[n_patches];

    for (int i = 0; i < n_patches; i++){
        x[i] = random_gen->uniform_int(0, this->BOARD_SIZE-1);
        y[i] = random_gen->uniform_int(0, this->BOARD_SIZE-1);
    }

    // Put individuals in these patches
    int n_indiv = params->N_INDIVIDUALS;
    int random_index, sex;
    Individual* indiv;

    for (int i = 0; i < n_indiv; i++){
        random_index = random_gen->uniform_int(0, n_patches-1);
        Patch* patch = this->get_patch(x[random_index], y[random_index]);
        if (i < int(n_indiv/2)){
            sex = FEMALE;
        }
        else{
            sex = MALE;
        }
        indiv = new Individual(patch, sex);
        patch->add_individual(indiv);
        this->mark_patch_occupied(patch);
    }
}

void Board::setup_initial_alleles(){
    Patch* patch;
    for (auto pair: this->occupied_patches){
        patch = pair.second;
        assert(patch != NULL);
        patch->setup_initial_alleles();
    }
}

void Board::migrate(){
    Patch* patch;
    double start_time = time_tracker->get_start_time();

    #if __DEBUG__
        // conservation of mass sanity check
        int total_pop_before = 0;
        for (int i = 0; i < this->BOARD_SIZE; i++){
            for (int j = 0; j < this->BOARD_SIZE; j++){
                total_pop_before += this->get_patch(i,j)->get_n_indiv();
            }
        }
    #endif


    for (auto obj: this->occupied_patches){
        patch = obj.second;
        patch->migrate();
    }


    this->occupied_patches.clear();
    for (int i = 0; i < this->BOARD_SIZE; i++){
        for (int j = 0; j < this->BOARD_SIZE; j++){
            if(this->get_patch(i,j)->get_n_indiv() > 0){
                this->mark_patch_occupied(this->get_patch(i,j));
            }
        }
    }

    #if __DEBUG__
        // conservation of mass sanity check
        int total_pop_after = 0;
        for (int i = 0; i < this->BOARD_SIZE; i++){
            for (int j = 0; j < this->BOARD_SIZE; j++){
                total_pop_after += this->get_patch(i,j)->get_n_indiv();
            }
        }

        assert(total_pop_after == total_pop_before && "num of indiv before and after migration is different!");

        Patch* debug_patch;

        // make sure all occupied patches are in occupied_patches and all unoccupied aren't
        for (int i = 0; i < this->BOARD_SIZE; i++){
            for (int j = 0; j < this->BOARD_SIZE; j++){
                debug_patch = this->get_patch(i,j);
                int hash_key = (long int) debug_patch;
                int n = debug_patch->get_n_indiv();
                if (n > 0){
                    assert(this->occupied_patches.find(hash_key) != this->occupied_patches.end() && "occupied patch not in vector of occupied patches!");
                }
                else{
                    if (this->occupied_patches.find(hash_key) != this->occupied_patches.end()){
                        printf("debug patch n: %d\n", debug_patch->get_n_indiv());
                    }
                    assert(this->occupied_patches.find(hash_key) == this->occupied_patches.end() && "unoccupied patch in vector of occupied patches!");
                }
            }
        }

    #endif
    time_tracker->add_time_in_migration(start_time);
}

void Board::selection(){
    double start_time = time_tracker->get_start_time();

    Patch* patch;
    for (auto obj: this->occupied_patches){
        patch = obj.second;
        patch->selection();
    }

    time_tracker->add_time_in_selection(start_time);
}

void Board::mating(){
    double start_time = time_tracker->get_start_time();

    Patch* patch;
    for (auto obj: this->occupied_patches){
        patch = obj.second;
        patch->mating();
    }

    time_tracker->add_time_in_mating(start_time);
}

void Board::census_pop(int gen){
    double start_time = time_tracker->get_start_time();

    Patch* patch;
    int n;
    std::vector<std::vector<int>> map(this->BOARD_SIZE,std::vector<int>(this->BOARD_SIZE));
    for (int i = 0; i < this->BOARD_SIZE; i++){
        for (int j = 0; j < this->BOARD_SIZE; j++){
            patch = this->get_patch(i,j);
            n = patch->get_n_indiv();
            map[i][j] = n;

            if (n > 0){

            }
        }
    }

    logger->write_generation_data(gen, map);
    time_tracker->add_time_in_census(start_time);
}

void Board::next_gen(int gen){
    this->fragment->fragment_more(gen);
}
