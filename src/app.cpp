/*----------Running lizard GAME----------*/

#include <graphics.h>
#include <iostream>
#include "Characters/lizard.h"
#include "GameObjects/food.h"
#include "GameObjects/poison.h"
#include "GameObjects/edible.h"
#include "GameObjects/grid.h"
#include "GameObjects/menu.h"
#include "Utilities/globals.h"
#include "Utilities/position.h"

inline void inputHandler(Lizard& body);
inline void generationHandler(Edible& f1, Poison& p, Lizard& b);

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
	Lives lives;
	Lizard body(&lives);
	Edible food;
	Poison poison;
	int length, count = 0;
	bool playing = true;
	int page = 1;
	int delayAmt = 50;

	food.generate(body.getPosX(), body.getPosY());
	poison.generate(body.getPosX(), body.getPosY());

	while (true)
	{
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();

		// Generate new pos for food
		if (food.update(body.getPosX(), body.getPosY())) {
			food.generate(body.getPosX(), body.getPosY());
			// body.getLivesADD()->decreaseLives();
			// std::cout << body.getLivesADD()->getLives();
		}

		if (poison.update(body.getPosX(), body.getPosY()))
		{
			poison.generate(body.getPosX(), body.getPosY());
			generationHandler(food, poison, body);
			body.getLivesADD()->decreaseLives();
			if (poison.getHit() == 3)
			{
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
				outtextxy(160, 545, (char*)"GAME OVER");
			}
		}

		grid = new Grid();

		// UI
		grid->draw();
		body.draw();
		food.draw("Assets/Sprites/a2KB.gif");
		poison.draw("Assets/Sprites/posion_potion.gif");

		inputHandler(body);
		body.drawLives();

		if (playing == true && !body.update())
			playing = false;

		// Exit 
		setcolor(WHITE);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
		settextjustify(0, 2);
		outtextxy(328, 580, (char*)"PRESS 'ESC' to EXIT");
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

// Generates new position if the position is equal to the food pos
inline void generationHandler(Edible& f, Poison& p, Lizard& b)
{
	if ((f.foodPos.x == p.foodPos.x && f.foodPos.y == p.foodPos.y))
	{
		p.generate(b.getPosX(), b.getPosY());
	}
}