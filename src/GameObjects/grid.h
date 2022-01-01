#ifndef GRID_H
#define GRID_H

#include <cstdint>
#include <graphics.h>
#include "../Utilities/globals.h"


class Grid {
private:
    uint8_t size = 30; // box 30 in grid
    int16_t left, top, right, bottom;
    int16_t x, y;
    uint8_t i;
    int16_t NODES[2][3] = { {0, 0, 0}, {0, 0, 0} }; // RGB color for grid nodes

public:
    Grid();
    Grid(uint8_t size);
    ~Grid();
    void draw();
};

#endif