#include <graphics.h>
#include <ctime> // Generate random numbers

class Poison : public Food
{
private:
	unsigned char hit = 0;
	
public:
	Poison();
	void draw() const;
	bool update(short int, short int);          // Status of food
	unsigned char getHit() const;
};

Poison::Poison() {}

void Poison::draw() const
{
	setcolor(GREEN);
	rectangle(foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
	setfillstyle(INTERLEAVE_FILL, GREEN);
	floodfill(foodPos.x + 15, foodPos.y + 15, GREEN);
}

bool Poison::update(short int lizardHeadx, short int lizardHeady) {
	if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady) {
		hit++;
		return true;
	}
	else
		return false;
}

unsigned char Poison::getHit() const
{
	return hit;
}