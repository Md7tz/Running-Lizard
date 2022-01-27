#ifndef MENU_H
#define MENU_H

#include <graphics.h>

class Menu
{
private:
    bool gameStart = false;             //bool attribute for telling if the game should start or not yet           
    bool gameOptions = false;           //bool attribute for telling if the current page is the options or not
    bool gameSound = true;              //bool attribute for telling if the game sound is ON or OFF
    bool prevGameSound = false;         //bool attribute for storing the previous game sound state for displaying purposes 
    bool arrowDown = false;             //bool attributes for storing the input of the user so we take the input only once
    bool arrowUp = false;               
    bool returnDown = false;                 

    int mainIndex = 0, prevMainIndex;   //store the current and previous index of the user choice in the menu
    int textX = 405, textY = 250;       //stores the primary text coordinates
    int textSpacing = 85;               //stores the spacing distance between texts
    int textFont = 2, textSize = 10;    //stores the font and size of the texts displayed

public:
    Menu();                                         //constructor
    ~Menu();                                        //destructor
    void displayMenu(int colorA, int colorB) const; //display method for the menu
    void arrows(int color, int i) const;            //display method for the arrows
    void displayOptionsPage();                      //display method for the options page
    void menuInputHandler();                        //helper method to identify and get user's input and choices in the menu
    void pagesHandler();                            //general display method that will handle displaying pages depending on user choice
    bool getGameState() const;                      //accessor to get the game state and decide if the game should start or not yet
};

#endif