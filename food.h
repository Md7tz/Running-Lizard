#include <graphics.h>
#include <ctime> // For Generating random numbers

class Food {
private:
     Position foodPos;
     int randInt;
public:
     static const int count;
     Food(int _randInt);
     void draw();                    // Draw the food on the graphics window
     void generate(int, int);        // Generate food everytime lizard eats it
     bool update(int, int);          // Status of food
     int getCount() const;
};

const int Food::count = 2;

Food::Food(int _randInt) {
     // count++;
     randInt = _randInt;
}

void Food::draw() {
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

     if (foodPos.x == lizardHeadx && foodPos.y == lizardHeady) {
          // Food::count--;
          return true;
     }
     else
          return false;
}

int Food::getCount() const {
     return count;
}