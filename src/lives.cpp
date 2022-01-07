#include "GameObjects/lives.h"

Lives::Lives() {
    numLives = 3;
}
void Lives::decreaseLives() {
    numLives--;
}

void Lives::reset() {
    numLives = 3;
}

int Lives::getLives() {
    return numLives;
}

void Lives::drawLives()
{
    /*
    draw the heart images on the screen
    */
	int x = 325, y = 540;
	if (numLives == 3) { readimagefile("Assets/Sprites/3heart.gif", x, y, x + 160, y - 40); }
	else if (numLives == 2) { readimagefile("Assets/Sprites/2H.gif", x, y, x + 160, y - 40); }
	else if (numLives == 1) { readimagefile("Assets/Sprites/1H.gif", x, y, x + 160, y - 40); }
}