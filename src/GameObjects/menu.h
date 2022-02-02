#ifndef MENU_H
#define MENU_H

#include <graphics.h>

class Menu
{
private:
    bool gameStart;             
    bool gameOptions;           
    bool gameSound;              
    bool prevGameSound;         
    bool arrowDown;             
    bool arrowUp;               
    bool returnDown;                 

    int mainIndex, prevMainIndex;   
    int textX, textY;       
    int textSpacing;               
    int textFont, textSize;    

public:
    Menu();                                         
    ~Menu();                                        
    void displayMenu(int colorA, int colorB) const; 
    void arrows(int color, int i) const;            
    void displayOptionsPage();                      
    void menuInputHandler();                        
    void pagesHandler();                            
    bool getGameState() const;                      
};

#endif