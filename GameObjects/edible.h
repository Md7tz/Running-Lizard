class Edible : public Food
{
public:
    static uint8_t count;
    Edible();
    Edible(uint8_t _randInt);
    ~Edible();

    bool update(int16_t, int16_t);	 // Status of food
    static uint8_t getCount();
};

uint8_t Edible::count = 0;

Edible::Edible() {}

Edible::Edible(uint8_t _randInt)
{
    count += 1;
    randInt = _randInt;
    foodColor = RED;
}

Edible::~Edible() {
    count -= 1;
}

bool Edible::update(int16_t lizardHeadx, int16_t lizardHeady)
{
    if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
        return true;
    else
        return false;
}

uint8_t Edible::getCount()
{
    return count;
}