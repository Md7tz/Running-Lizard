class Poison : public Food
{
private:
	uint8_t hit = 0;
	
public:
	Poison();
	~Poison();
	
	void draw() const;
	bool update(int16_t, int16_t);          // Status of food
	uint8_t getHit() const;
};

Poison::Poison() {}

Poison::~Poison() {}

void Poison::draw() const
{
	setcolor(GREEN);
	rectangle(foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
	setfillstyle(INTERLEAVE_FILL, GREEN);
	floodfill(foodPos.x + 15, foodPos.y + 15, GREEN);
}

bool Poison::update(int16_t lizardHeadx, int16_t lizardHeady) {
	if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady) {
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