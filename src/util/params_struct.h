
#ifndef PARAMS_STRUCTH
#define PARAMS_STRUCTH

#include "include.h"

// Struct with all possible parameters.
// Takes on values from params.h by default,
// but can be overridden with cmd line options

typedef struct params_s{
    params_s(){
        RUN_DATA_DIR = "";
        BOARD_SIZE = BOARD_SIZE_DEFAULT;
        N_ENV_FACTORS = N_ENV_FACTORS_DEFAULT;
        N_GENERATIONS = N_GENERATIONS_DEFAULT;
        FRAGMENT_AMOUNT_LOW = FRAGMENT_AMOUNT_LOW_DEFAULT;
        FRAGMENT_AMOUNT_HI = FRAGMENT_AMOUNT_HI_DEFAULT;
        FRAGMENT_H_VALUE = FRAGMENT_H_VALUE_DEFAULT;
        FRAGMENT_PROBABILITY = FRAGMENT_PROBABILITY_DEFAULT;
        ENV_FACTOR_CUTOFF = ENV_FACTOR_CUTOFF_DEFAULT;
        ENV_FACTOR_H_VALUE = ENV_FACTOR_H_VALUE_DEFAULT;
    }
    std::string RUN_DATA_DIR;
    int BOARD_SIZE;
    int N_ENV_FACTORS;
    int N_GENERATIONS;
    float FRAGMENT_AMOUNT_LOW;
    float FRAGMENT_AMOUNT_HI;
    float FRAGMENT_H_VALUE;
    float FRAGMENT_PROBABILITY;
    float ENV_FACTOR_CUTOFF;
    float ENV_FACTOR_H_VALUE;
} params_s;

#endif
