
#ifndef BOARD_H
#define BOARD_H

struct point{
            int x;
            int y;
};

class Board{
    private:
        int grid;
        int individuals;
        int hotspots;
    public:
        void print_hello();
        void pick_hotspots();
        void allocate_individuals();
        void migrate();
        void next_gen();

};


#endif
