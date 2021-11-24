class Rgb
{
public:
    int16_t H[3] = {0, 0, 0};                     // RGB color for lizard head
    int16_t B[3] = {0, 0, 0};                     // RGB color for lizard body
    int16_t EH[3] = {0, 0, 0};                    // RGB color for lizard head
    int16_t EB[3] = {0, 0, 0};                    // RGB color for lizard body
    int16_t NODES[2][3] = {{0, 0, 0}, {0, 0, 0}}; // RGB color for grid nodes
    int16_t FOOD = RED;                           // color for food
    int16_t POISON = GREEN;                       // color for poison

    Rgb();
    ~Rgb();
};

Rgb::Rgb()
{
    H[0] = 179; H[1] = 170; H[2] = 0;
    B[0] = 245; B[1] = 232; B[2] = 0;
    EH[0] = 0; EH[1] = 0; EH[2] = 0;
    EB[0] = 66; EB[1] = 67; EB[2] = 69;
    NODES[0][0] = 204; NODES[0][1] = 255; NODES[0][2] = 204;
    NODES[1][0] = 229; NODES[1][1] = 255; NODES[1][2] = 204;
}

Rgb::~Rgb() {}