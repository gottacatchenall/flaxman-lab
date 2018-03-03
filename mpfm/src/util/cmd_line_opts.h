#ifndef CMD_LINE_OPTS_H
#define CMD_LINE_OPTS_H

#include "include.h"
#include <iostream>
#include <unistd.h>

#if __APPLE__
  #include <mach-o/dyld.h>
#endif


// Struct with all possible parameters.
// Takes on values from params.h by default,
// but can be overridden with cmd line options

typedef struct params_s{
    params_s(){
        BOARD_SIZE = BOARD_SIZE_DEFAULT;
        N_ENV_FACTORS = N_ENV_FACTORS_DEFAULT;
        ENV_FACTOR_MODE = ENV_FACTOR_MODE_DEFAULT;
    }
    int BOARD_SIZE;
    int N_ENV_FACTORS;
    int ENV_FACTOR_MODE;
} params_s;


void printHello();
void printUsage(char* name);
params_s* get_options(int argc, char*argv[], params_s* opts);
char* get_execuable_path(char* dirNameBuffer, int bufSize);


#endif
