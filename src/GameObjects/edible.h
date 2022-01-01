#ifndef EDIBLE_H
#define EDIBLE_H

#include "food.h"

class Edible : public Food
{
private:
    static const uint8_t count;
public:
    Edible();
    Edible(uint8_t _randInt);
    ~Edible();

    bool update(int16_t, int16_t);	 // Status of food
    static uint8_t getCount();
};

#endif