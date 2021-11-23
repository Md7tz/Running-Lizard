class Grid {
private:
    Rgb* rgb;
    UBYTE size = 30; // box 30 in grid
    DBYTE left, top, right, bottom;
    DBYTE x, y;
    UBYTE i;

public:
    Grid();
    Grid(UBYTE size);
    ~Grid();
    void drawGrid();
};

Grid::Grid() : x(5), y(5), left(0), top(0), right(size), bottom(size), i(0) {
    rgb = new Rgb;
}

Grid::Grid(UBYTE size) : Grid() {
    this->size = size;
}

Grid::~Grid() {}

void Grid::drawGrid()
{   // Color A: 229 255 204
    // Color B: 204 255 204

    // setcolor(COLOR(204, 255, 204));
    // fill background with color first
    setfillstyle(fill_styles::SOLID_FILL, COLOR(rgb->NODES[0][0], rgb->NODES[0][1], rgb->NODES[0][2]));
    floodfill(x, y, COLOR(rgb->NODES[0][0], rgb->NODES[0][1], rgb->NODES[0][2]));

    // Divide background to grid containers and fill with color
    setcolor(COLOR(rgb->NODES[1][0], rgb->NODES[1][1], rgb->NODES[1][2]));
    for (UBYTE row = 0; row < HEIGHT / size; row++)
    {
        for (UBYTE col = 0; col < WIDTH / size; col++)
        {
            rectangle(left, top, right, bottom);
            left += size;
            right += size;
            if (i % 2 == 0)
            {
                setfillstyle(fill_styles::SOLID_FILL, COLOR(rgb->NODES[1][0], rgb->NODES[1][1], rgb->NODES[1][2]));
                floodfill(x, y, COLOR(rgb->NODES[1][0], rgb->NODES[1][1], rgb->NODES[1][2]));
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
