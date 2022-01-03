/*----------Running lizard GAME----------*/

#include <graphics.h>
#include <iostream>
#include "Characters/lizard.h"
#include "GameObjects/food.h"
#include "GameObjects/edible.h"
#include "GameObjects/grid.h"
#include "GameObjects/menu.h"
#include "Utilities/globals.h"
#include "Utilities/position.h"

inline void inputHandler(Lizard& body);

int main()
{
	initwindow(WIDTH, HEIGHT, "Running Lizard", (getmaxwidth() - WIDTH) / 2, (getmaxheight() - HEIGHT) / 2);

	Menu* menu;
	// Menu block
	menu = new Menu();
	while (!(menu->getGameState()))
	{
		menu->pagesHandler();
		menu->menuInputHandler();
		delay(100);
	}
	menu = NULL;
	delete menu;

start:
	Grid* grid;
	Lizard body;
	Edible food;
	int length, count = 0;
	bool playing = true;
	int page = 1;
	int delayAmt = 50;

	food.generate(body.getPosX(), body.getPosY());

	while (true)
	{
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();

		if (food.update(body.getPosX(), body.getPosY()))
			food.generate(body.getPosX(), body.getPosY());

		grid = new Grid();

		// UI
		grid->draw();
		body.draw();
		food.draw();

		inputHandler(body);

		if (playing == true && !body.update())
			playing = false;

		// Exit 
		setcolor(WHITE);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
		settextjustify(0, 2);
		outtextxy(326, 580, (char*)"PRESS 'ESC' to EXIT");
		// Restart
		if (GetAsyncKeyState('R'))
			goto start;

		page = 1 - page;
		delay(delayAmt);
		delete grid;
	}

	getch();
	closegraph();
}

inline void inputHandler(Lizard& body) {
	if (GetAsyncKeyState(VK_LEFT))
		body.changeDir(LEFT);
	if (GetAsyncKeyState(VK_UP))
		body.changeDir(UP);
	if (GetAsyncKeyState(VK_RIGHT))
		body.changeDir(RIGHT);
	if (GetAsyncKeyState(VK_DOWN))
		body.changeDir(DOWN);
	if (GetAsyncKeyState(VK_ESCAPE))
		exit(1);
}
