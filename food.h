#include <graphics.h>
#include <ctime> // For Generating random numbers

class Food {
private:
     int randInt;
public:
     Position foodPos;
     static const int count;
     Food();
     Food(int _randInt);
     void draw() const;              // Draw the food 
     void generate(int, int);        // Generate food pos
     bool update(int, int);          // Status of food
     int getCount() const;
};

const int Food::count = 2;

Food::Food() {}

Food::Food(int _randInt) {
     randInt = _randInt;
}

void Food::draw() const{
     setcolor(RED);
     rectangle(foodPos.x, foodPos.y, foodPos.x + 30, foodPos.y + 30);
     setfillstyle(INTERLEAVE_FILL, RED);
     floodfill(foodPos.x + 15, foodPos.y + 15, RED);
}

void Food::generate(int lizardHeadx, int lizardHeady) {  // Generate new pos for the Object
     if (Food::count == 2) {
          srand(time(0));
          foodPos.x = 30 * ((rand() + randInt) % 20 + 1);
          srand(time(0));
          foodPos.y = 30 * ((rand() + randInt) % 15 + 1);
          if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
               generate(lizardHeadx, lizardHeady);
     }
}

bool Food::update(int lizardHeadx, int lizardHeady) {
     if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady)
          return true;
     else
          return false;
}

int Food::getCount() const {
     return count;
}