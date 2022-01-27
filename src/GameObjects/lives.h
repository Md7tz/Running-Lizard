#ifndef LIVES_H
#define LIVES_H

#include <cstdint>
#include <graphics.h>

class Lives {
private:
    int numLives;

public:
    Lives();
    void decreaseLives();
    void reset();
    int getLives();
	void drawLives();
};

#endif