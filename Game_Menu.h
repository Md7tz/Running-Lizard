
#include <graphics.h>
class GameMenu
{
public:
	bool change_role=true;
	int arrow_color = 14;
	int box_color = 11;
	int text_color = 14;

public:
	void arrow_1(int color);
	void arrow_2(int color);
	void menu(int box_color, int text_color);
	void showMenu(bool &change_role);
	void moveUp(bool &change_role);
	void moveDown(bool &change_role);

	GameMenu() {}
};
void GameMenu::arrow_1(int color)
{
	setcolor(color);
	int points[8] = {170, 190, 220 - 10, 210, 170, 230, 170, 190};
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, color);
	fillpoly(4, points);
}
void GameMenu::arrow_2(int color)
{
	setcolor(color);
	int points[8] = {170, 240, 220 - 10, 260, 170, 280, 170, 240};
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, color);
	fillpoly(4, points);
}
void GameMenu::menu(int box_color, int text_color)
{
	setcolor(box_color);
	for (int i = 0; i < 10; i++)
		rectangle(110 - i, 150 - i, 580 + i, 430 + i);

	setcolor(text_color);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
	outtextxy(240, 200, "START");
	outtextxy(240, 250, "Exit");
}

void GameMenu::showMenu(bool &change_role)
{
	if (change_role)
	{
		if (!GetAsyncKeyState(VK_UP))
		{
			menu(box_color, text_color);
			arrow_1(arrow_color);
		}
	}
}
void GameMenu::moveUp(bool &change_role)
{
	if (GetAsyncKeyState(VK_UP))
	{
		cleardevice();
		menu(box_color, text_color);
		arrow_1(arrow_color);
        change_role = true;
	}
}
void GameMenu::moveDown(bool &change_role)
{
	if (GetAsyncKeyState(VK_DOWN) || !change_role)
	{
		cleardevice();
		change_role = false;
		menu(box_color, text_color);
		arrow_2(arrow_color);
	}
}