#include <graphics.h>

class Menu
{
private:
    bool gameStart = false, gameOptions = false, gameHtp = false, gameSound = true;
    int mainIndex = 1;

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
    void options();
    void htp();
    void menuInputHandler();
    void pagesHandler();
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
    if (mainIndex == 1) settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY, (char*)"START");
#pragma endregion

#pragma region Options
    settextstyle(textFont, HORIZ_DIR, textSize);
    if (mainIndex == 2) settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY + textSpacing, (char*)"OPTIONS");
#pragma endregion

#pragma region HTP
    settextstyle(textFont, HORIZ_DIR, textSize);
    if (mainIndex == 3) settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY + 2 * textSpacing, (char*)"HOW TO PLAY");
#pragma endregion

#pragma region Exit
    settextstyle(textFont, HORIZ_DIR, textSize);
    if (mainIndex == 4) settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY + 3 * textSpacing, (char*)"EXIT");
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
void Menu:: options()
{  
    if(GetAsyncKeyState(VK_ESCAPE)) gameOptions=false;
    
    if(GetAsyncKeyState(VK_RETURN)) {
        gameSound = !gameSound;
        if(gameSound) PlaySound("Assets/SFX/background music .wav", NULL, SND_ASYNC);
    }

    cleardevice();

    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    settextjustify(0, 2);
    outtextxy(10, 10, (char*)"Press 'ESC' to go back");

    setcolor(YELLOW);
    settextstyle(10, HORIZ_DIR, 5);
    settextjustify(1, 1);
    outtextxy(textX, textY, (char*)"Sound");

    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    settextjustify(1, 1);
    outtextxy(textX, textY + textSpacing, (char*)"Press 'ENTER' to turn ON/OFF the Game Sound");
    
    setcolor(GREEN);
    setfillstyle(SOLID_FILL,GREEN);
    if(gameSound==false) {
        setcolor(DARKGRAY);
        setfillstyle(SOLID_FILL,DARKGRAY);
        PlaySound(NULL, 0, 0);
    }
    ellipse(textX, textY + 40, 0, 360, 40, 10);
    fillellipse(textX, textY + 40, 40, 10);
}
void Menu:: htp()
{
    if(GetAsyncKeyState(VK_ESCAPE)) gameHtp=false;

    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    settextjustify(0, 2);
    outtextxy(10, 10, (char*)"Press 'ESC' to go back");

    //how to play text
    settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY, (char*)"How to Play");
}
void Menu:: menuInputHandler()
{    
    if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
        if (mainIndex > 1)
            mainIndex--;
    if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
        if (mainIndex < 4)
            mainIndex++;
    if (GetAsyncKeyState(VK_RETURN))
    {
        if (mainIndex == 1)
            gameStart = true;
        if (mainIndex == 2)
            gameOptions = true;
        if (mainIndex == 3)
            gameHtp = true;
        if (mainIndex == 4)
            exit(1);
    }
}
void Menu :: pagesHandler()
{
    cleardevice();

    if(gameOptions) options();

    if(gameHtp) htp();

    if(!gameHtp & !gameOptions){
    if (mainIndex == 1)
    {
        menu(LIGHTGRAY, YELLOW);
        arrows1(DARKGRAY);
    }
    if (mainIndex == 2)
    {
        menu(LIGHTGRAY, YELLOW);
        arrows2(DARKGRAY);
    }
    if (mainIndex == 3)
    {
        menu(LIGHTGRAY, YELLOW);
        arrows3(DARKGRAY);
    }
    if (mainIndex == 4)
    {
        menu(LIGHTGRAY, YELLOW);
        arrows4(DARKGRAY);
    }
    }
}
bool Menu :: getGameState() const
{
    return gameStart;
}