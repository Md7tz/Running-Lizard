
#include <graphics.h>
class GameMenu
{
private:
	int arrowColor = 14;
	int boxColor = 11;
	int textColor = 14;
	int key = 0;

public:
	void arrow_1();
	void arrow_2();
	void draw();
	void detectInput();
	void showOption(bool &nextPage, bool &keyDown);
	int getKeyState();

	GameMenu();
	~GameMenu();
};

GameMenu::GameMenu()
{
	key = 0;
}
GameMenu::~GameMenu() {}

void GameMenu::arrow_1()
{
	setcolor(arrowColor);
	int points[8] = {170, 190, 220 - 10, 210, 170, 230, 170, 190};
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, arrowColor);
	fillpoly(4, points);
}

void GameMenu::arrow_2()
{
	setcolor(arrowColor);
	int points[8] = {170, 240, 220 - 10, 260, 170, 280, 170, 240};
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, arrowColor);
	fillpoly(4, points);
}

void GameMenu::draw()
{
	setcolor(boxColor);
	for (int i = 0; i < 10; i++)
		rectangle(110 - i, 150 - i, 580 + i, 430 + i);

	setcolor(textColor);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
	outtextxy(240, 200, (char*)"START");
	outtextxy(240, 250, (char*)"EXIT");
}

void GameMenu::detectInput()
{
	if (GetAsyncKeyState(VK_UP))
		key = 0;
	if (GetAsyncKeyState(VK_DOWN))
		key = 1;

	if (key == 0)
	{
		cleardevice();
		draw();
		arrow_1();
	}
	else
	{
		cleardevice();
		draw();
		arrow_2();
	}
}
void GameMenu::showOption(bool &nextPage, bool &keyDown)
{
	while (nextPage)
	{
		swapbuffers();
		readimagefile("Assets/Sprites/mainMenu.jpg", 0, 0, 810, 600);
		if (GetAsyncKeyState(VK_RETURN))
		{
			if (!keyDown)
			{
				swapbuffers();
				nextPage = false;
				keyDown = true;
				break;
			}
		}
		else
			keyDown = false;
	}
}
	

int GameMenu::getKeyState()
{
	return key;
}