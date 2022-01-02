class Food
{
protected:
	uint8_t randInt;
	int foodColor;

public:
	Position foodPos;
	void draw() const;				 		 // Draw the food
	void generate(int16_t, int16_t); 		 // Generate food position
	virtual bool update(int16_t, int16_t);	 // Status of food

};

// void Food::draw() const
// {
// 	setcolor(foodColor);
// 	readimagefile("apple.gif",foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
// 	// setfillstyle(INTERLEAVE_FILL, foodColor);
// 	// floodfill(foodPos.x + 15, foodPos.y + 15, foodColor);
// }

// // Generate new pos for the Object
// void Food::generate(int16_t headX, int16_t headY)
// {
// 	foodPos.x = 30 * ((rand() + randInt) % 20 + 1);
// 	foodPos.y = 30 * ((rand() + randInt) % 15 + 1);
// 	if (foodPos.x == headX && foodPos.y == headY)
// 		generate(headX, headY);
// }

// bool Food::update(int16_t lizardHeadx, int16_t lizardHeady)
// {
// 	if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
// 		return true;
// 	else
// 		return false;
// }