class Grid {
private:
    // Rgb* rgb;
    uint8_t size; // box 30 in grid
    int16_t left, top, right, bottom;
    int16_t x, y;
    uint8_t i;
    const int16_t HEIGHT = 600, WIDTH = 810;

public:
    Grid();
    Grid(uint8_t size);
    ~Grid();
    void drawGrid();
};

Grid::Grid() {
    size = 30; // box size in grid
    left = 0, top = 0, right = 30, bottom = 30;
    x = 5, y = 5;
    i = 0;
}

Grid::Grid(uint8_t size) : x(5), y(5), left(0), top(0), right(this->size), bottom(this->size), i(0) {
    this->size = size;
    // rgb = new Rgb;
}

Grid::~Grid() {}

inline void Grid::drawGrid()
{   // Color A: 229 255 204
    // Color B: 204 255 204

    // setcolor(COLOR(204, 255, 204));
    // fill background with color first
    setfillstyle(fill_styles::SOLID_FILL, COLOR(204, 255, 204));
    floodfill(x, y, COLOR(204, 255, 204));

    // Divide background to grid containers and fill with color
    setcolor(COLOR(229, 255, 204));
    for (uint8_t row = 0; row < HEIGHT / 30; row++)
    {
        for (uint8_t col = 0; col < WIDTH / 30; col++)
        {
            rectangle(left, top, right, bottom);
            left += 30;
            right += 30;
            if (i % 2 == 0)
            {
                setfillstyle(fill_styles::SOLID_FILL, COLOR(229, 255, 204));
                floodfill(x, y, COLOR(229, 255, 204));
            }
            x += 30;
            i++;
        }
        left = 0;
        right = 30;
        top += 30;
        bottom += 30;
        x = 5;
        y += 30;
    }
}
