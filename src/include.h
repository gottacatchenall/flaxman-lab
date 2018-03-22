// Universal includes

#include "params.h"
#include "util/constants.h"
#include "util/macros.h"
#include <iostream>
#include <assert.h>

// Forward Declars
class Board;
class EnvFactor;
class Fragment;
class Patch;
class Individual;
class Genome;

class Logger;
class Fractal;
class Random;
class TimeTracker;

struct params_s;
typedef params_s params_s;
struct genetic_map_s;
typedef genetic_map_s genetic_map_s;

// Externs
extern Random* random_gen;
extern Fractal* fractal;
extern Logger* logger;
extern params_s* params;
extern genetic_map_s* genetic_map;
extern TimeTracker* time_tracker;
