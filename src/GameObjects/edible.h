#ifndef EDIBLE_H
#define EDIBLE_H

#include "food.h"

class Edible : public Food
{
public:
    Edible();
    Edible(uint8_t _randInt);
    ~Edible();

    bool update(int16_t, int16_t);	 // Status of food
};

#endif