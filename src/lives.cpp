#include "GameObjects/lives.h"

Lives::Lives() {
    numLives = 3;
}
void Lives::decrease() {
    numLives--;
}

void Lives::reset() {
    numLives = 3;
}

int Lives::getCount() {
    return numLives;
}

void Lives::draw()
{
    /*
    draw the heart images on the screen
    */
	int x = 325, y = 550;
	if (numLives == 3) { readimagefile("Assets/Sprites/3heart.gif", x, y, x + 160, y - 40); }
	else if (numLives == 2) { readimagefile("Assets/Sprites/2heart.gif", x, y, x + 160, y - 40); }
	else if (numLives == 1) { readimagefile("Assets/Sprites/1heart.gif", x, y, x + 160, y - 40); }
}

void Lives::operator -=(int n)
{
    numLives -= n;
}

bool Lives::operator ==(int n)
{
   return (numLives==n);
}
