#ifndef FOOD_H
#define FOOD_H

#include <cstdint>
#include <string>
#include <graphics.h>
#include "../Utilities/position.h"

class Food
{
protected:
	uint8_t randInt; 
	Position foodPos; 
public:
	void draw(std::string filepath) const;				 		 // Draw the food
	void generate(int16_t, int16_t); 		 // Generate food position
	virtual bool update(int16_t, int16_t);	 // Status of food
	Position getPos();

};

#endif