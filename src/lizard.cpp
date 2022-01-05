#include "Characters/lizard.h"
#include <iostream>

void Lizard::draw()
{
	/*
	* DRAWING THE WHOLE lizard
	* Colors
	* 179, 170, 0
	* 245, 232, 0
	*/
	for (int i = 0; i < length; i++)
	{
		setcolor(YELLOW);
		rectangle(arr[i].x, arr[i].y, arr[i].x + 30, arr[i].y + 30);
		if (i == 0)
			setfillstyle(SOLID_FILL, COLOR(179, 170, 0)); 	  // HEAD IS OF DIFFERENT COLOR
		else                                                  // REST OF THE BODY
			setfillstyle(SOLID_FILL, COLOR(245, 232, 0));
		floodfill(arr[i].x + 15, arr[i].y + 15, YELLOW);
	}
}

void Lizard::changeDir(int newdir)
{

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

int Lizard::update()
{

	for (int i = 1; i < length; ++i)
	{
		if (arr[0].x == arr[i].x && arr[0].y == arr[i].y)
			return 0;
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
		arr[0].x -= 30;
		if (arr[0].x == 0)
		{
			arr[0].x = 750; // -30
		}
	}
	else if (direction == RIGHT)
	{
		arr[0].x += 30;
		if (arr[0].x == 780) //  -30
		{
			arr[0].x = 30;
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
			arr[0].y = 30;
		}
	}
	return 1;
}

int Lizard::getPosX() {
	return arr[0].x;
}

int Lizard::getPosY() {
	return arr[0].y;
}

int Lizard::getLength() {
	return length;
}

Lives* Lizard::getLivesADD() {
	return lives;
}
void Lizard::drawLives()
{
	int x = 325, y = 540;
	if (getLivesADD()->getLives() == 3) { readimagefile("Assets/Sprites/3heart.gif", x, y, x + 160, y - 40); }
	else if (getLivesADD()->getLives() == 2) { readimagefile("Assets/Sprites/2H.gif", x, y, x + 160, y - 40); }
	else if (getLivesADD()->getLives() == 1) { readimagefile("Assets/Sprites/1H.gif", x, y, x + 160, y - 40); }
}
