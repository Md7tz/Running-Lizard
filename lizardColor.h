#include <graphics.h>
class lizardColor
{
public:
    int headColor[3]; // this variable will store the RGB color for lizard head
    int bodyColor[3]; // this variable will store the RGB color for lizard body
    lizardColor()
    {
        headColor[0] = 179; headColor[1] = 179; headColor[2] = 0;
        bodyColor[0] = 245; bodyColor[1] = 232; bodyColor[2] = 0;
    }
};