
#include "Fragment.h"
#include "Fractal.h"
#include "Random.h"
#include "Logger.h"
#include "params_struct.h"

Fragment::Fragment(){
    assert(params->FRAGMENT_AMOUNT_LOW < 1 && params->FRAGMENT_AMOUNT_LOW > 0);
    assert(params->FRAGMENT_AMOUNT_HI < 1 && params->FRAGMENT_AMOUNT_HI > 0);
    assert(params->FRAGMENT_AMOUNT_LOW <= params->FRAGMENT_AMOUNT_HI);
    assert(params->FRAGMENT_PROBABILITY > 0 && params->FRAGMENT_PROBABILITY);

    this->BOARD_SIZE = params->BOARD_SIZE;
    this->FRAGMENT_AMOUNT_LOW = params->FRAGMENT_AMOUNT_LOW;
    this->FRAGMENT_AMOUNT_HI = params->FRAGMENT_AMOUNT_HI;
    this->FRAGMENT_H_VALUE = params->FRAGMENT_H_VALUE;
    this->FRAGMENT_PROBABILITY = params->FRAGMENT_PROBABILITY;

    this->fragment_map = this->create_fragment_map();

    int** grid = new int*[this->BOARD_SIZE];
    for (int i = 0; i < this->BOARD_SIZE; i++){
        grid[i] = new int[this->BOARD_SIZE];
    }

    for (int i = 0; i < this->BOARD_SIZE; i++){
        for (int j = 0; j < this->BOARD_SIZE; j++){
            grid[i][j] = 1;
        }
    }

    this->fragment_grid = grid;

    this->setup_fragment_heap();
}

int** Fragment::create_fragment_map(){
    int** map = fractal->create_binary_map_from_fractal(fractal->generate_fractal(0.1), 0.2);
    for (int i = 0; i < this->BOARD_SIZE; i++){
        for (int j = 0; j < this->BOARD_SIZE; j++){
            map[i][j] = 0;
        }
    }

    int x,y;
    std::vector<int> x_vals;
    std::vector<int> y_vals;
    bool new_coord;
    double frac = 0.0;
    double lower = params->FRAGMENT_AMOUNT_LOW;
    while (frac < lower){
        x = random_gen->uniform_int(0,this->BOARD_SIZE-1);
        y = random_gen->uniform_int(0,this->BOARD_SIZE-1);
        new_coord = true;
        for (int i = 0; i < x_vals.size(); i++){
            if (x_vals[i] == x && y_vals[i] == y){
                new_coord = false;
            }
        }
        if (new_coord){
            x_vals.push_back(x);
            y_vals.push_back(y);
        }
        frac = float(x_vals.size())/float(this->BOARD_SIZE*this->BOARD_SIZE);
    }

    for (int i = 0; i < x_vals.size(); i++){
        x = x_vals[i];
        y = y_vals[i];
        map[x][y] = 1;
    }

    return map;
}

int Fragment::count_zeros(int **map){
    int c = 0;

    for (int i = 0; i < this->BOARD_SIZE; i++){
        for (int j = 0; j < this->BOARD_SIZE; j++){
            if (map[i][j] == 0){
                c++;
            }
        }
    }
    return c;
}

void Fragment::setup_fragment_heap(){
    for (int i = 0; i < this->BOARD_SIZE; i++){
        for (int j = 0; j < this->BOARD_SIZE; j++){
            if (this->fragment_map[i][j] == 0){
                int key = random_gen->uniform_int(0, 1000);
                fragment_point *tmp = new fragment_point(i, j, key);
                this->fragment_heap.push(tmp);
            }
        }
    }
}

std::vector<int> Fragment::fragment_more(int gen){
    double ran = random_gen->uniform_float(0.0, 1.0);
    if (ran < this->FRAGMENT_PROBABILITY){
        if (this->fragment_heap.size() > 0){
            fragment_point *pt = this->fragment_heap.top();
            this->fragment_heap.pop();
            this->set_cell_value(pt->x, pt->y, 0);
            logger->write_fragmentation_data(gen, pt->x, pt->y);
            std::vector<int> point_vec(pt->x, pt->y);
            free(pt);
            return point_vec;
        }
    }
    logger->write_fragmentation_data(gen, -1, -1);
    return std::vector<int>();
}

void Fragment::set_cell_value(int x, int y, int val){
    this->fragment_grid[x][y] = val;
}

int Fragment::get_cell_value(int x, int y){
    return this->fragment_map[x][y];
}

int Fragment::get_board_size(){
    return this->BOARD_SIZE;
}
