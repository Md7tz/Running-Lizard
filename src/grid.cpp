#include "GameObjects/grid.h"

Grid::Grid() : x(5), y(5), left(0), top(0), right(size), bottom(size), i(0) {
    /*
    assign the colors' rgb values that will fill the boxes.
    */
    NODES[0][0] = 204; NODES[0][1] = 255; NODES[0][2] = 204;
    NODES[1][0] = 229; NODES[1][1] = 255; NODES[1][2] = 204;
}

Grid::Grid(uint8_t size) : Grid() {
    /*
    invoke the default constructor and 
    assign the new value for the box size
    */
    this->size = size;
}

Grid::~Grid() {}

void Grid::draw()
{   // Color A: 229 255 204
    // Color B: 204 255 204

    // setcolor(COLOR(204, 255, 204));
    // fill background with color first
    setfillstyle(fill_styles::SOLID_FILL, COLOR(NODES[0][0], NODES[0][1], NODES[0][2]));
    floodfill(x, y, COLOR(NODES[0][0], NODES[0][1], NODES[0][2]));

    // Divide background to grid containers and fill with color
    setcolor(COLOR(NODES[1][0], NODES[1][1], NODES[1][2]));
    for (uint8_t row = 0; row < HEIGHT / size; row++)
    {
        for (uint8_t col = 0; col < WIDTH / size; col++)
        {
            rectangle(left, top, right, bottom);
            left += size;
            right += size;
            if (i % 2 == 0)
            {
                setfillstyle(fill_styles::SOLID_FILL, COLOR(NODES[1][0], NODES[1][1], NODES[1][2]));
                floodfill(x, y, COLOR(NODES[1][0], NODES[1][1], NODES[1][2]));
            }
            x += size;
            i++;
        }
        left = 0;
        right = size;
        top += size;
        bottom += size;
        x = 5;
        y += size;
    }
}
