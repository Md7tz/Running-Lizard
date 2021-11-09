#include <graphics.h>

enum DIR { LEFT, UP, RIGHT, DOWN };        // ENUM MAKES THE WORK EASY BY PROVIDING NAMES INSTEAD OF NUMBERS

struct Position {
        int x, y;
        Position()
        {
                x = -50;
                y = 0;
        }
};

////// lizard CLASS //////
class LizardBody
{
private:
        Position arr[31];            // ThiS ARRAY IS GOING TO CONTAIN THE POSITIONS OF WHOLE lizard
        int direction;
        int length;
public:
        LizardBody()
        {
                arr[0].x = 30;        // PROVIDING THE lizardHEAD ITS INITIAL VALUE
                arr[0].y = 30;        // PROVIDING THE lizardHEAD ITS INITIAL VALUE
                length = 2;           // INITILAL LENGTH = 2
                direction = RIGHT;    // GOING IN RIGHT DIRECTION
        }
        void drawLizard();
        void appendLizard();         // IT IS RESPONSIBLE FOR INCREMENT IN lizard'S LENGTH
        void changeDirTo(int);
        int update();
        int getPosx();              // THESE FUNCTIONS ARE FOR OBVIOUS PURPOSES
        int getPosy();              // THESE FUNCTIONS ARE FOR OBVIOUS PURPOSES
        int getlength();            // THESE FUNCTIONS ARE FOR OBVIOUS PURPOSES

};

void LizardBody::drawLizard() {    // DRAWING THE WHOLE lizard

        for (int i = 0; i < length; i++)
        {
                setcolor(BLUE);
                rectangle(arr[i].x, arr[i].y, arr[i].x + 30, arr[i].y + 30);
                if (i == 0)
                        setfillstyle(SOLID_FILL, GREEN);        // HEAD IS OF DIFFERENT COLOR
                else                                            // REST OF THE BODY
                        setfillstyle(SOLID_FILL, LIGHTGREEN);
                floodfill(arr[i].x + 15, arr[i].y + 15, BLUE);
        }
}

void LizardBody::appendLizard() {
        if (length < 30)                            // PREVENTS THE LENGTH FROM GOING GREATER THAN 29
                length++;
}

void LizardBody::changeDirTo(int newdir) {

        if (newdir == LEFT || newdir == RIGHT)
        {
                if (direction == UP || direction == DOWN)
                        direction = newdir;
        }
        else if (newdir == UP || newdir == DOWN)
        {
                if (direction == LEFT || direction == RIGHT)
                        direction = newdir;
        }
}

int LizardBody::update() {                                            // THIS FUNCTION ENFORCES THE BASIC
                                                                      // ALGORITHM FOR MOVING lizard
        for (int i = 1; i < length; ++i)                              // BY PROVIDING ALL THE PREVIOUS PARTS
        {                                                             // THE COORDINATES OF CURRENT PART
                if (arr[0].x == arr[i].x && arr[0].y == arr[i].y)     // HENCE [1] GETS THE POSITION OF [0]
                {                                                     // [2] GETS THE POSITION OF [1] AND SO ON...
                        return 0;                                     // AND LASTLY HEAD([0]) IS GIVEN LATEST VALUES
                }
        }
        for (int i = length; i >= 0; --i)
        {
                if (i == 0)
                {
                        arr[1].x = arr[0].x;
                        arr[1].y = arr[0].y;
                }
                else
                {
                        arr[i].x = arr[i - 1].x;
                        arr[i].y = arr[i - 1].y;
                }
        }
        if (direction == LEFT)
        {
                int offsetX = 30;
                arr[0].x -= 30;
                if (arr[0].x+offsetX == 0)
                {
                        // arr[0].x -= 30;
                        arr[0].x = 780; // 510 - 60
                }
        }
        else if (direction == RIGHT)
        {
                arr[0].x += 30;
                if (arr[0].x == 810) // 510 - 30
                {
                        arr[0].x = 0;
                }
        }
        else if (direction == UP)
        {
                arr[0].y -= 30;
                if (arr[0].y == 0)
                {
                        arr[0].y = 510;
                }
        }
        else if (direction == DOWN)
        {
                arr[0].y += 30;
                if (arr[0].y == 540)
                {
                        arr[0].y = 0;
                }
        }
        return 1;
}

int LizardBody::getPosx()
{
        return arr[0].x;
}

int LizardBody::getPosy()
{
        return arr[0].y;
}

int LizardBody::getlength()
{
        return length;
}