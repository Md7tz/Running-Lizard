class Food
{
protected:
	uint8_t randInt;
	int foodColor;
	Rgb* rgb;

public:
	Position foodPos;
	static const uint8_t count;
	Food();
	Food(uint8_t _randInt);
	// ~Food();

	void draw() const;				 // Draw the food
	void generate(int16_t, int16_t); // Generate food position
	bool update(int16_t, int16_t);	 // Status of food

	uint8_t getCount() const;
};

const uint8_t Food::count = 2;

Food::Food() {}
Food::Food(uint8_t _randInt)
{
	randInt = _randInt;
	rgb = new Rgb;
	foodColor = rgb->FOOD;
}
// Food::~Food()
// {
// 	if (rgb != NULL) {
// 		delete rgb;
// 		rgb = NULL;
// 	}
// }

void Food::draw() const
{
	setcolor(foodColor);
	rectangle(foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
	setfillstyle(INTERLEAVE_FILL, foodColor);
	floodfill(foodPos.x + 15, foodPos.y + 15, foodColor);
}

// Generate new pos for the Object
void Food::generate(int16_t headX, int16_t headY)
{
	if (Food::count == 2)
	{
		srand(time(NULL));
		foodPos.x = 30 * ((rand() + randInt) % 20 + 1);
		srand(time(NULL));
		foodPos.y = 30 * ((rand() + randInt) % 15 + 1);
		if (foodPos.x == headX && foodPos.y == headY)
			generate(headX, headY);
	}
}

bool Food::update(int16_t lizardHeadx, int16_t lizardHeady)
{
	if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
		return true;
	else
		return false;
}

uint8_t Food::getCount() const
{
	return count;
}