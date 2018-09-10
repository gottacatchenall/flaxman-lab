#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include "include.h"

class TimeTracker{
    private:
        double total_start_time;
        double time_in_logger;
        double time_in_migration;
        double time_in_selection;
        double time_in_setup;
        double time_in_random_gen;
        double time_in_mating;
        double time_in_census;
    public:
        TimeTracker();
        double get_start_time();
        void add_time_in_logger(double start);
        void add_time_in_migration(double start);
        void add_time_in_selection(double start);
        void add_time_in_mating(double start);
        void add_time_in_random(double start);
        void add_time_in_census(double start);
        void print_times();
};

#endif
