
#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "include.h"
#include <queue>

class Random;
class Fractal;
class Logger;

struct params_s;
typedef params_s params_s;

typedef struct fragment_point{
    fragment_point(int x0, int y0, int key0){
        x = x0;
        y = y0;
        key = key0;
    }
    int x;
    int y;
    int key;
} fragment_point;


// Overload Compare to have fragent_heap work on fragment_points
class Compare{
    public:
        bool operator() (fragment_point* a, fragment_point* b){
            if (a->key > b->key){ return true; }
            return false;
        }
};

class Fragment{
    private:
        int BOARD_SIZE;
        float FRAGMENT_AMOUNT_LOW;
        float FRAGMENT_AMOUNT_HI;
        float FRAGMENT_H_VALUE;
        float FRAGMENT_PROBABILITY;
        int** fragment_grid;
        int** fragment_map;
        std::priority_queue<fragment_point*, std::vector<fragment_point*>, Compare> fragment_heap;
        Fractal* fractal;
        Random* random;
        Logger* logger;
    public:
        Fragment(Random* random, Fractal* fractal, Logger* logger, params_s* params);
        int** create_fragment_map();
        int count_zeros(int **map);
        void fragment_more(int gen);
        void setup_fragment_heap();
        int get_board_size();
        void set_cell_value(int x, int y, int val);
        int get_cell_value(int x, int y);
};

#endif
