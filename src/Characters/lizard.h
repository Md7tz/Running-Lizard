#include <graphics.h>
#include "../Utilities/position.h"

class Lizard
{
private:
        Position arr[31]; // ThiS ARRAY IS GOING TO CONTAIN THE POSITIONS OF WHOLE lizard
        int direction;
        int length;

public:
        Lizard()
        {
                arr[0].x = 30;     // PROVIDING THE lizardHEAD ITS INITIAL VALUE
                arr[0].y = 30;     // PROVIDING THE lizardHEAD ITS INITIAL VALUE
                length = 2;        // INITILAL LENGTH = 2
                direction = RIGHT; // GOING IN RIGHT DIRECTION
        }
        void drawLizard();
        void appendLizard(); // IT IS RESPONSIBLE FOR INCREMENT IN lizard'S LENGTH
        void changeDirTo(int);
        int update();
        int getPosx();   // THESE FUNCTIONS ARE FOR OBVIOUS PURPOSES
        int getPosy();   // THESE FUNCTIONS ARE FOR OBVIOUS PURPOSES
        int getlength(); // THESE FUNCTIONS ARE FOR OBVIOUS PURPOSES
};

