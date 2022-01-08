#ifndef EDIBLE_H
#define EDIBLE_H

#include "food.h"

class Edible : public Food
{
public:
    Edible();
    Edible(uint8_t _randInt);
    ~Edible();
};

#endif