#include "edible.h"

const uint8_t Edible::count = 2;

Edible::Edible() {}
Edible::Edible(uint8_t _randInt)
{
    randInt = _randInt;
    foodColor = RED;
}

Edible::~Edible() {}

bool Edible::update(int16_t lizardHeadx, int16_t lizardHeady)
{
    if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
        return true;
    else
        return false;
}

uint8_t Edible::getCount()
{
    return count;
}