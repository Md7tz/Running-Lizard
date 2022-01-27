#ifndef LIVES_H
#define LIVES_H

#include <cstdint>
#include <graphics.h>

class Lives {
private:
    int numLives;

public:
    Lives();
    void operator -=(int);
    bool operator ==(int);
    void decrease();
    void reset();
    int getCount();
    void draw();
};

#endif