#ifndef LIVES_H
#define LIVES_H

#include <cstdint>

class Lives {
private:
    int n_lives;

public:
    Lives();
    void decreaseLives();
    void reset();
    int getLives();
};

#endif