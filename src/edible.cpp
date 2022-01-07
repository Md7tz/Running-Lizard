#include "GameObjects/edible.h"

Edible::Edible()
{}

Edible::Edible(uint8_t _randInt)
{
    randInt = _randInt;
}

Edible::~Edible() {}

bool Edible::update(int16_t lizardHeadx, int16_t lizardHeady)
{
    /*
    check if the lazard head is in the 
    same box of the of the edible box, 
    in other words if the lizard has 
    eaten the edible.
    */
    if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
        return true;
    else
        return false;
}
