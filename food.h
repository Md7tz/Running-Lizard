class Food
{
protected:
	uint8_t randInt;
	int food_color;
	Rgb *rgb = new Rgb;

public:
	Position foodPos;
	static const uint8_t count;
	Food();
	Food(uint8_t _randInt);
	~Food();

	void draw() const;				 // Draw the food
	void generate(int16_t, int16_t); // Generate food position
	bool update(int16_t, int16_t);	 // Status of food

	uint8_t getCount() const;
};

const uint8_t Food::count = 2;

Food::Food() {}
Food::~Food()
{
	delete rgb;
}
Food::Food(uint8_t _randInt)
{
	randInt = _randInt;
	food_color = rgb->Food;
}

void Food::draw() const
{
	setcolor(food_color);
	rectangle(foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
	setfillstyle(INTERLEAVE_FILL, food_color);
	floodfill(foodPos.x + 15, foodPos.y + 15, food_color);
}

// Generate new pos for the Object
void Food::generate(int16_t lizardHeadx, int16_t lizardHeady)
{
	if (Food::count == 2)
	{
		srand(time(0));
		foodPos.x = 30 * ((rand() + randInt) % 20 + 1);
		srand(time(0));
		foodPos.y = 30 * ((rand() + randInt) % 15 + 1);
		if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
			generate(lizardHeadx, lizardHeady);
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