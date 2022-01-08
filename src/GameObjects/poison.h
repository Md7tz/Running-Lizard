#ifndef POISON_H
#define POISON_H

#include "food.h"
#include "edible.h"

class Poison : public Food
{
private:
	uint8_t hit = 0;
public:
	Poison();
	~Poison();
	bool update(int16_t, int16_t); // Status of food
	uint8_t getHit() const;
};

#endif