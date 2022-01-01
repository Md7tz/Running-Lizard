#ifndef FOOD_H
#define FOOD_H

#include <cstdint>
#include <graphics.h>
#include "position.h"

class Food
{
protected:
	uint8_t randInt;
	int foodColor;

public:
	Position foodPos;
	Food();
	void draw() const;				 		 // Draw the food
	void generate(int16_t, int16_t); 		 // Generate food position
	virtual bool update(int16_t, int16_t);	 // Status of food

};

#endif