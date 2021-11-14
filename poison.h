#include <graphics.h>
#include <ctime> // For Generating random numbers
#include <cstdlib>
#include <iostream>
class poison : public  Food
{
private:
  int hit = 0;
  int randInt;
public:
  poison(int);
  int getHit() const;
  void draw();
  bool update(int, int);          // Status of food

};

void poison::draw()
{
  setcolor(GREEN);
  rectangle(foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
  setfillstyle(INTERLEAVE_FILL, GREEN);
  floodfill(foodPos.x + 15, foodPos.y + 15, GREEN);
}

int poison::getHit() const
{
  return hit;
}

poison::poison(int _randInt) {
  randInt = _randInt;
}

bool poison::update(int lizardHeadx, int lizardHeady) {

  if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady) {
    hit++;
    return true;
  }
  else
    return false;
}

