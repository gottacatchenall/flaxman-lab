
#ifndef ENVFACTOR_H
#define ENVFACTOR_H

#include <vector>

class EnvFactor{
    private:
        int x0;
        int y0;

        typedef std::vector< std::vector<uint8_t> > matrix;
        matrix grid;
    public:
      EnvFactor();
};

#endif
