#include <graphics.h>
#include <ctime> // For Generating random numbers

class Poison : public Food
{
private:
  int hit = 0;
public:
  Poison();
  void draw() const;
  bool update(int, int);          // Status of food
  int getHit() const;
};

Poison::Poison(){}

void Poison::draw() const
{
  setcolor(GREEN);
  rectangle(foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
  setfillstyle(INTERLEAVE_FILL, GREEN);
  floodfill(foodPos.x + 15, foodPos.y + 15, GREEN);
}

bool Poison::update(int lizardHeadx, int lizardHeady) {
  if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady) {
    hit++;
    return true;
  }
  else
    return false;
}

int Poison::getHit() const
{
  return hit;
}