#ifndef MENU_H
#define MENU_H

#include <graphics.h>

class Menu
{
private:
    bool gameStart = false;
    bool gameOptions = false;
    bool gameSound = true, prevGameSound = false;
    bool arrowDown = false;
    bool arrowUp = false;
    bool returnDown = false;

    int mainIndex = 0, prevMainIndex;
    int textX = 405, textY = 250;
    int textSpacing = 85;
    int textFont = 2, textSize = 10;

public:
    Menu();
    void menu(int colorA, int colorB) const;
    void arrow(int color, int i) const;
    void options();
    void menuInputHandler();
    void pagesHandler();
    bool getGameState() const;
};

#endif