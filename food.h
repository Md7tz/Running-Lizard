#include <graphics.h>
#include <ctime> // For Generating random numbers

class Food {
private:
	unsigned char randInt;

public:
	Position foodPos;
	static const unsigned char count;
	Food();
	Food(unsigned char _randInt);

	void draw() const;                          // Draw the food 
	void generate(short int, short int);        // Generate food position
	bool update(short int, short int);          // Status of food

	unsigned char getCount() const;
};

const unsigned char Food::count = 2;

Food::Food() {}

Food::Food(unsigned char _randInt) {
	randInt = _randInt;
}

void Food::draw() const {
	setcolor(RED);
	rectangle(foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
	setfillstyle(INTERLEAVE_FILL, RED);
	floodfill(foodPos.x + 15, foodPos.y + 15, RED);
}

// Generate new pos for the Object
void Food::generate(short int lizardHeadx, short int lizardHeady) {
	if (Food::count == 2) {
		srand(time(0));
		foodPos.x = 30 * ((rand() + randInt) % 20 + 1);
		srand(time(0));
		foodPos.y = 30 * ((rand() + randInt) % 15 + 1);
		if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
			generate(lizardHeadx, lizardHeady);
	}
}

bool Food::update(short int lizardHeadx, short int lizardHeady) {
	if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
		return true;
	else
		return false;
}

unsigned char Food::getCount() const {
	return count;
}