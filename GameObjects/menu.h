#include <graphics.h>

class Menu
{
private:
    bool gameStart = false, gameOptions = false, gameHTP = false;
    int index = 1;

    int textX = 405, textY = 250;
    int textSpacing = 85;
    int textFont = 2, textSize = 10;

public:
	Menu();
    void menu(int titleC, int buttonsC) const;
    void arrows1(int color1) const;
    void arrows2(int color2) const;
    void arrows3(int color3) const;
    void arrows4(int color4) const;
	void options() const;
	void htp() const;
    void MenuInputHandler();
    void PagesHandler();
	bool getGameState() const;
};

Menu :: Menu () {};
void Menu :: menu(int titleC, int buttonsC) const
{
#pragma region Title
    setcolor(titleC);
    settextstyle(textFont, HORIZ_DIR, 30);
    settextjustify(1, 1);
    outtextxy(textX, 100, (char *)"Running Lizard");
#pragma endregion

    setcolor(buttonsC);

#pragma region Start
    settextstyle(textFont, HORIZ_DIR, textSize);
    if(index==1) settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY, (char *)"START");
#pragma endregion

#pragma region Options
    settextstyle(textFont, HORIZ_DIR, textSize);
    if(index==2) settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY + textSpacing, (char *)"OPTIONS");
#pragma endregion

#pragma region HTP
    settextstyle(textFont, HORIZ_DIR, textSize);
    if(index==3) settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY + 2 * textSpacing, (char *)"HOW TO PLAY");
#pragma endregion

#pragma region Exit
    settextstyle(textFont, HORIZ_DIR, textSize);
    if(index==4) settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY + 3 * textSpacing, (char *)"EXIT");
#pragma endregion

}
void Menu :: arrows1(int color1) const
{
    setcolor(color1);
    int points1[8] = {textX - 110, textY - 26, textX - 95, textY - 13, textX - 110, textY};
    drawpoly(3, points1);
    setfillstyle(SOLID_FILL, color1);
    fillpoly(3, points1);
    int point1[8] = {textX + 105, textY - 26, textX + 90, textY - 13, textX + 105, textY};
    drawpoly(3, point1);
    fillpoly(3, point1);
}
void Menu :: arrows2(int color2) const
{
    setcolor(color2);
    int points2[8] = {textX - 135, textY + textSpacing - 26, textX - 120, textY + textSpacing - 13, textX - 135, textY + textSpacing};
    drawpoly(3, points2);
    setfillstyle(SOLID_FILL, color2);
    fillpoly(3, points2);

    int point2[8] = {textX + 135, textY + textSpacing - 26, textX + 120, textY + textSpacing - 13, textX + 135, textY + textSpacing};
    drawpoly(3, point2);
    fillpoly(3, point2);
}
void Menu :: arrows3(int color3) const
{
    setcolor(color3);
    int points3[8] = {textX - 195, textY + 2 * textSpacing - 26, textX - 180, textY + 2 * textSpacing - 13, textX - 195, textY + 2 * textSpacing};
    drawpoly(3, points3);
    setfillstyle(SOLID_FILL, color3);
    fillpoly(3, points3);

    int point3[8] = {textX + 190, textY + 2 * textSpacing - 26, textX + 175, textY + 2 * textSpacing - 13, textX + 190, textY + 2 * textSpacing};
    drawpoly(3, point3);
    fillpoly(3, point3);
}
void Menu :: arrows4(int color4) const
{
    setcolor(color4);
    int points4[8] = {textX - 75, textY + 3 * textSpacing - 26, textX - 60, textY + 3 * textSpacing - 13, textX - 75, textY + 3 * textSpacing};
    drawpoly(3, points4);
    setfillstyle(SOLID_FILL, color4);
    fillpoly(3, points4);

    int point4[8] = {textX + 70, textY + 3 * textSpacing - 26, textX + 55, textY + 3 * textSpacing - 13, textX + 70, textY + 3 * textSpacing};
    drawpoly(3, point4);
    fillpoly(3, point4);
}
void Menu :: options() const
{

}
void Menu :: htp() const
{

}
void Menu :: MenuInputHandler()
{
    if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
        if (index > 1)
            index--;
    if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
        if (index < 4)
            index++;
    if (GetAsyncKeyState(VK_ESCAPE))
        exit(1);
    if (GetAsyncKeyState(VK_RETURN))
    {
        if (index == 1)
            gameStart = true;
        if (index == 2)
            gameOptions = true;
        if (index == 3)
            gameHTP = true;
        if (index == 4)
            exit(1);
    }
}
void Menu :: PagesHandler()
{
    cleardevice();
    if (index == 1)
    {
        menu(LIGHTGRAY, YELLOW);
        arrows1(DARKGRAY);
    }
    if (index == 2)
    {
        menu(LIGHTGRAY, YELLOW);
        arrows2(DARKGRAY);
    }
    if (index == 3)
    {
        menu(LIGHTGRAY, YELLOW);
        arrows3(DARKGRAY);
    }
    if (index == 4)
    {
        menu(LIGHTGRAY, YELLOW);
        arrows4(DARKGRAY);
    }
}
bool Menu :: getGameState() const
{
	return gameStart;
}