#include <graphics.h>
#include "position.h"
#include <ctime> // For Generating random numbers

class Food {
private:
     Position foodPos;
public:
     void draw();                    // Draw the food on the graphics window
     void generate(int, int);        // Generate food everytime lizard eats it
     bool update(int, int);          // Status of food(whether it is been eaten or not)
};


