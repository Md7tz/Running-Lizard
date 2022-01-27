#ifndef FOOD_H
#define FOOD_H

#include <cstdint>
#include <graphics.h>
#include "../Utilities/position.h"

class Food
{
protected:
	uint8_t randInt;
	int foodColor;

public:
	virtual bool update(int16_t, int16_t) = 0;	 // Status of food
	
	Position foodPos;
	void draw(std::string filepath) const;		 // Draw the food
	void generate(int16_t, int16_t); 		 	 // Generate food position
};

#endif