#include "TimeTracker.h"

TimeTracker::TimeTracker(){
    this->time_in_logger = 0;
    this->time_in_migration = 0;
    this->time_in_setup = 0;
    this->time_in_random_gen = 0;
    this->time_in_mating = 0;
    this->time_in_selection = 0;
    this->time_in_census = 0;
    this->total_start_time = clock();
}

double TimeTracker::get_start_time(){
    return double(clock());
}

void TimeTracker::add_time_in_logger(double start){
    this->time_in_logger += float( clock () - start ) /  CLOCKS_PER_SEC;
}

void TimeTracker::add_time_in_migration(double start){
    this->time_in_migration += float( clock () - start ) /  CLOCKS_PER_SEC;
}

void TimeTracker::add_time_in_random(double start){
    this->time_in_random_gen += float( clock () - start ) /  CLOCKS_PER_SEC;
}


void TimeTracker::add_time_in_selection(double start){
    this->time_in_selection += float( clock () - start ) /  CLOCKS_PER_SEC;
}

void TimeTracker::add_time_in_mating(double start){
    this->time_in_mating += float( clock () - start ) /  CLOCKS_PER_SEC;
}

void TimeTracker::add_time_in_setup(double start){
    this->time_in_setup += float( clock () - start ) /  CLOCKS_PER_SEC;
}

void TimeTracker::add_time_in_census(double start){
    this->time_in_census += float( clock () - start ) /  CLOCKS_PER_SEC;
}


void TimeTracker::print_times(){
    double total_run_time = float( clock () - this->total_start_time ) /  CLOCKS_PER_SEC;

    printf("\n\nTime in setup: %.2fsec\n", this->time_in_setup);
    printf("Time in migration: %.2fsec\n", this->time_in_migration);
    printf("Time in selection: %.2fsec\n", this->time_in_selection);
    printf("Time in mating: %.2fsec\n", this->time_in_mating);
    printf("Time in random generation: %.2fsec\n", this->time_in_random_gen);
    printf("Time in census: %.2fsec\n", this->time_in_census);
    printf("Time in logger: %.2fsec\n", this->time_in_logger);
    printf("-------------------------------\n");
    printf("Total run time: %.2fsec\n", total_run_time);
}
