#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include "include.h"

class TimeTracker{
    private:
        double total_start_time;
        double time_in_logger;
        double time_in_migration;
        double time_in_setup;
    public:
        TimeTracker();
        double get_start_time();
        void add_time_in_logger(double start);
        void add_time_in_migration(double start);
        void add_time_in_setup(double start);
        void print_times();
};

#endif
