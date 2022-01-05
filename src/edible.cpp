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
    if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
        return true;
    else
        return false;
}
