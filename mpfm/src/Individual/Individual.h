
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H


class Individual{
    private:
        int genome;
        point location;
    public:
        void get_initial_alleles();
        void migrate();
        void get_fitness();
        void choose_mate();
        void reproduce(Individual mate);
};

#endif
