class Poison : public Food
{
private:
	UBYTE hit = 0;
	
public:
	Poison();
	~Poison();
	
	void draw() const;
	bool update(DBYTE, DBYTE);          // Status of food
	UBYTE getHit() const;
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

bool Poison::update(DBYTE lizardHeadx, DBYTE lizardHeady) {
	if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady) {
		hit++;
		return true;
	}
	else
		return false;
}

UBYTE Poison::getHit() const
{
	return hit;
}