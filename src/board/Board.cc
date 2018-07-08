
#include "Board.h"
#include "Patch.h"
#include "EnvFactor.h"
#include "Random.h"
#include "Logger.h"
#include "Fractal.h"
#include "Individual.h"
#include "Fragment.h"
#include "TimeTracker.h"
#include "GeneTracker.h"
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
// Initialization
// ===============================================
    // these methods are only called once: after the board is constructed  but before the sim begins


/*  Board::allocate_individuals()
        Allocates a total of N individuals into a maximum of P patches, where N = params->N_INDIVIDUALS,
        and P = params->N_MAX_INIT_OCCUPIED_PATCHES.
*/
void Board::allocate_individuals(){

    // Pick locations of patches that will be initially occupied
    int n_patches = params->N_MAX_INIT_OCCUPIED_PATCHES;
    int x;
    int y;
    int n_indiv = params->N_INDIVIDUALS;
    int random_index, sex;
    Individual* indiv;

    for (int i = 0; i < n_patches; i++){
        x = random_gen->uniform_int(0, this->BOARD_SIZE-1);
        y = random_gen->uniform_int(0, this->BOARD_SIZE-1);
        for (int i = 0; i < n_indiv; i++){
            random_index = random_gen->uniform_int(0, n_patches-1);
            Patch* patch = this->get_patch(x, y);
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
}

/* Board::setup_initial_alleles()
    Sets up the initial genotype of all of the individuals. The distribution of alleles,
    and the allelic values, and unique to each patch.
*/
void Board::setup_initial_alleles(){
    Patch* patch;
    for (auto pair: this->occupied_patches){
        patch = pair.second;
        assert(patch != NULL);
        patch->setup_initial_alleles();
    }
}


// ===============================================
// Core Methods
// ===============================================
    // Each of these methods are called once per generation

void Board::migrate(){
    Patch* patch;
    double start_time = time_tracker->get_start_time();

    #if __DEBUG__
        int total_pop_before = this->check_num_of_indivs();
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
        this->check_occupied_patches_vector();
        int total_pop_after = this->check_num_of_indivs();
        assert(total_pop_after == total_pop_before && "num of indiv before and after migration is different!");
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
                patch->census_patch();
            }
        }
    }

    int n_total = this->get_total_num_indivs();

    logger->write_generation_data(gen, map, n_total);

    gene_tracker->erase_data();
    time_tracker->add_time_in_census(start_time);
}

void Board::next_gen(int gen){
    std::vector<int> fragment_point = this->fragment->fragment_more(gen);
    if (!fragment_point.empty()){
        if (this->on_board(fragment_point[0], fragment_point[1])){
            this->get_patch(fragment_point[0], fragment_point[1])->mark_patch_fragmented();
        }
    }
}

// ===============================================
// Miscellaneous utility methods
// ===============================================

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

/*  Board::on_board(int x, int y)
        Returns true if (x,y) is on the board, false if it isn't.
*/
bool Board::on_board(int x, int y){
    if (x < 0 || x >= this->BOARD_SIZE || y < 0 || y >= this->BOARD_SIZE){
        return false;
    }
    return true;
}

/*  Board::get_surrounding_patches(int x, int y)
        Returns a vector of all patches a distance M or less from the patch (x,y), where
        M = params->MIGRATION_DISTANCE.
*/
std::vector<Patch*> Board::get_surrounding_patches(int x, int y){
    int migration_dist = params->MIGRATION_DISTANCE;
    std::vector<Patch*> surrounding_patches;
    Patch* tmp;

    for (int i = -1*migration_dist; i <= migration_dist; i++){
        for (int j = -1*migration_dist; j <= migration_dist; j++){
            if (!(i == 0 && j == 0) && this->on_board(x+i, y+j)){
                tmp = this->get_patch(x+i, y+j);
                if (tmp->is_fragmented() == false){
                    surrounding_patches.push_back(tmp);
                }
            }
        }
    }

    return surrounding_patches;
}

// ===============================================
// Setters and Getters
// ===============================================

/*  Board::get_patch(int x, int y)
        Returns a pointer to the Patch object with location (x,y)
*/
Patch* Board::get_patch(int x, int y){
    if (this->on_board(x,y)){
        return this->grid[x][y];
    }
    printf("patch off board: %d %d \n", x,y);
    return NULL;
}


/*  Board::get_envFactor_value(int x, int y, int envFactor)
        Returns the value of the envFactor-th environmental factor at the location (x,y)
*/
int Board::get_envFactor_value(int x, int y, int envFactor){
    return this->envFactors[envFactor]->get_cell_value(x,y);
}

int Board::get_total_num_indivs(){
    int pop = 0;
    for (int i = 0; i < this->BOARD_SIZE; i++){
        for (int j = 0; j < this->BOARD_SIZE; j++){
            pop += this->get_patch(i,j)->get_n_indiv();
        }
    }

    return pop;
}

// ===============================================
// Testing and Validation
// ===============================================
#if __DEBUG__


/*  Board::check_num_of_indivs()
        Counts the number of individuals across all patches.
        Used to make sure the same number of indivs exist before/after migration.
*/
int Board::check_num_of_indivs(){
    int pop = 0;
    for (int i = 0; i < this->BOARD_SIZE; i++){
        for (int j = 0; j < this->BOARD_SIZE; j++){
            pop += this->get_patch(i,j)->get_n_indiv();
        }
    }

    return pop;
}

/*  Board::check_occupied_patches_vector()
        Checks to make sure the vector this->occupied_patches only contains
        patches that are occupied, and that there aren't any occupied patches that
        aren't in the occupied_patches vector. .
*/
void Board::check_occupied_patches_vector(){
    Patch* debug_patch;

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
}

#endif
