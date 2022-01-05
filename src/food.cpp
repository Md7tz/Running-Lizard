#include "GameObjects/food.h"
#include <graphics.h>
#include <iostream>
// #include "Assets/apple.gif"

void Food::draw(std::string filepath) const
{
	readimagefile(filepath.c_str(), foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
}

// Generate new pos for the Object
void Food::generate(int16_t headX, int16_t headY)
{
	foodPos.x = 30 * ((rand() + randInt) % 20 + 1);
	foodPos.y = 30 * ((rand() + randInt) % 15 + 1);
	if (foodPos.x == headX && foodPos.y == headY)
		generate(headX, headY);
}

bool Food::update(int16_t lizardHeadx, int16_t lizardHeady)
{
	if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
		return true; 
	return false;
}
Position Food::getPos(){return foodPos;}