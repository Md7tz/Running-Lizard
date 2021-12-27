#include "food.h"

void Food::draw() {
     setcolor(RED);
     rectangle(foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
     setfillstyle(INTERLEAVE_FILL, RED);
     floodfill(foodPos.x + 15, foodPos.y + 15, RED);
}

void Food::generate(int lizardHeadx, int lizardHeady) {
     srand(time(0));
     foodPos.x = 30 * (rand() % 15 + 1);
     srand(time(0));
     foodPos.y = 30 * (rand() % 15 + 1);
     if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
          generate(lizardHeadx, lizardHeady);
}

bool Food::update(int lizardHeadx, int lizardHeady) {
     if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
          return true;
     else
          return false;
}