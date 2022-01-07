#include "GameObjects/poison.h"

Poison::Poison()
{}

Poison::~Poison() {}

bool Poison::update(int16_t lizardHeadx, int16_t lizardHeady)
{
	/*
	check if the lizard has eaten the poison
	*/
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