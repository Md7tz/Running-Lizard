#include "GameObjects/menu.h"
#include <iostream>
Menu::Menu() : gameStart(false),
               gameOptions(false),
               gameSound(true),
               prevGameSound(false),
               arrowDown(false),
               arrowUp(false),
               returnDown(false),
               mainIndex(0),
               prevMainIndex(-1), 
               textX(405),
               textY(250),
               textSpacing(85),
               textFont(2),
               textSize(10) {};

Menu::~Menu() {}

void Menu::displayMenu(int titleC, int buttonsC) const
{
    setcolor(titleC);
    settextstyle(textFont, HORIZ_DIR, 30);
    settextjustify(1, 1);
    outtextxy(textX, 100, (char *)"Running Lizard");

    setcolor(buttonsC);
    settextstyle(textFont, HORIZ_DIR, textSize);
    if (mainIndex == 0)
        settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY, (char *)"START");

    settextstyle(textFont, HORIZ_DIR, textSize);
    if (mainIndex == 1)
        settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY + textSpacing, (char *)"OPTIONS");

    settextstyle(textFont, HORIZ_DIR, textSize);
    if (mainIndex == 2)
        settextstyle(10, HORIZ_DIR, 5);
    outtextxy(textX, textY + 2 * textSpacing, (char *)"EXIT");
}

void Menu::arrows(int color, int i) const
{
    /*
    draw the aside arrows
    */
    int left[8] = {textX - 135, textY + i * textSpacing - 26, textX - 120, textY + i * textSpacing - 13, textX - 135, textY + i * textSpacing};
    int right[8] = {textX + 135, textY + i * textSpacing - 26, textX + 120, textY + i * textSpacing - 13, textX + 135, textY + i * textSpacing};

    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, WHITE);
    drawpoly(3, left);
    fillpoly(3, left);
    drawpoly(3, right);
    fillpoly(3, right);
}

void Menu::displayOptionsPage(bool & SFX)
{
    /*
    provide the user with the option
    settings in case the user has hit
    the home key on the option choice
    */
    if (GetAsyncKeyState(VK_ESCAPE))
    {
        gameOptions = false;
        if (gameSound)
            prevGameSound = false;
        else
            prevGameSound = true;
        SFX=gameSound;
        std::cout<<SFX<<"\n";
        
    }

    if (GetAsyncKeyState(VK_RETURN))
    {
        returnDown = true;
    }
    else if (!GetAsyncKeyState(VK_RETURN) && returnDown == true)
    {
        gameSound = !gameSound;
        // if (gameSound)
            // PlaySound("Assets/SFX/background music.wav", NULL, SND_ASYNC);
        returnDown = false;
    }

    if (prevGameSound != gameSound)
    {
        cleardevice();

        setcolor(LIGHTGRAY);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        settextjustify(0, 2);
        outtextxy(10, 10, (char *)"Press 'ESC' to go back");

        setcolor(YELLOW);
        settextstyle(10, HORIZ_DIR, 5);
        settextjustify(1, 1);
        outtextxy(textX, textY, (char *)"Sound");

        setcolor(LIGHTGRAY);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        settextjustify(1, 1);
        outtextxy(textX, textY + textSpacing, (char *)"Press 'ENTER' to turn ON/OFF the Game Sound");

        setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);

        if (gameSound == false)
        {
            setcolor(LIGHTGRAY);
            setfillstyle(SOLID_FILL, LIGHTGRAY);
            // PlaySound(NULL, 0, 0);
        }
        ellipse(textX, textY + 40, 0, 360, 40, 10);
        fillellipse(textX, textY + 40, 40, 10);

        prevGameSound = gameSound;
    }
}

void Menu::menuInputHandler()
{
    /*
    determine which choice of the menu
    the user has chosen
    */
    if (GetAsyncKeyState(VK_UP))
    {
        arrowUp = true;
    }
    else if (!GetAsyncKeyState(VK_UP) && arrowUp == true)
    {
        if (mainIndex > 0)
            mainIndex--;
        arrowUp = false;
    }

    if (GetAsyncKeyState(VK_DOWN))
    {
        arrowDown = true;
    }
    else if (!GetAsyncKeyState(VK_DOWN) && arrowDown == true)
    {
        if (mainIndex < 2)
            mainIndex++;
        arrowDown = false;
    }

    if (GetAsyncKeyState(VK_RETURN))
    {
        prevMainIndex = mainIndex + 1; //reset prevIndex to be different than mainIndex

        if (mainIndex == 0)
            gameStart = true;
        else if (mainIndex == 1)
            gameOptions = true;
        else if (mainIndex == 2)
            exit(1);
    }
}

void Menu::pagesHandler(bool &SFX)
{
    /*
    to update the graphical page based on the user
    choice of menu options
    */
    if (gameOptions)
        displayOptionsPage(SFX);

    if ((gameOptions == false) && (mainIndex != prevMainIndex))
    {
        cleardevice();

        if (mainIndex == 0)
            arrows(GREEN, mainIndex);
        else if (mainIndex == 1)
            arrows(GREEN, mainIndex);
        else if (mainIndex == 2)
            arrows(GREEN, mainIndex);

        displayMenu(LIGHTGRAY, YELLOW);

        prevMainIndex = mainIndex;
    }
}

bool Menu::getGameState() const
{
    return gameStart;
}