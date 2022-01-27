#include "GameObjects/food.h"

// Generate new pos for the Object
void Food::draw(std::string filepath) const
{
	readimagefile(filepath.c_str(), foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
}

void Food::generate(int16_t headX, int16_t headY)
{
	foodPos.x = 30 * ((rand() + randInt) % 20 + 1);
	foodPos.y = 30 * ((rand() + randInt) % 15 + 1);
	if (foodPos.x == headX && foodPos.y == headY)
		generate(headX, headY);
}