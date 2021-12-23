#include "GameObjects/poison.h"

Poison::Poison()
{
	foodColor = GREEN;
}

Poison::~Poison() {}

bool Poison::update(int16_t lizardHeadx, int16_t lizardHeady)
{
	if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
	{
		hit++;
		return true;
	}
	else
		return false;
}
uint8_t Poison::getHit() const
{
	return hit;
}