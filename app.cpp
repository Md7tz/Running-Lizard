/*----------Running lizard GAME----------*/

#include <graphics.h>
#include <iostream>
#include "lizard.h"
#include "food.h"
#include "edible.h"
#include "grid.h"
#include "globals.h"


using namespace std;


int main()
{
     initwindow(WIDTH, HEIGHT, "Running Lizard");

start:
     Lizard body;
     Food fruit;
     int length, count = 0;
     bool playing = true;
     int page = 1;
     Grid* grid;
     

     fruit.generate(body.getPosx(), body.getPosy());

     while (true)
     {
          setactivepage(page);
          setvisualpage(1 - page);
          cleardevice();
          		grid = new Grid();
		grid->draw();

          setcolor(BLUE);
          setfillstyle(SOLID_FILL, BLUE);

          if (GetAsyncKeyState(VK_LEFT))
          {
               body.changeDirTo(LEFT);
          }
          if (GetAsyncKeyState(VK_UP))
          {
               body.changeDirTo(UP);
          }
          if (GetAsyncKeyState(VK_RIGHT))
          {
               body.changeDirTo(RIGHT);
          }
          if (GetAsyncKeyState(VK_DOWN))
          {
               body.changeDirTo(DOWN);
          }
          if (GetAsyncKeyState(VK_ESCAPE))
               break;
          if (GetAsyncKeyState('R')) // 0x52 R key
               goto start;

          if (playing == true && !body.update())
          {
               playing = false;
          }

          // UI
          body.drawLizard();

          if (fruit.update(body.getPosx(), body.getPosy()))
          {
               fruit.generate(body.getPosx(), body.getPosy());
          }

          // Exit the game
          settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
          outtextxy(580, 545, (char*)"PRESS 'ESC' to EXIT");

          fruit.draw();
          delete grid;
          page = 1 - page;
          delay(150);
     }

     getch();
     closegraph();
}

// Initial state grid with no borders
// void drawBorders()
// {
//      setcolor(DARKGRAY);
//      rectangle(0, 0, 30, 600);     // LEFT BORDER
//      rectangle(780, 0, 810, 610);  // RIGHT BORDER
//      rectangle(30, 0, 780, 30);    // TOP BORDER
//      rectangle(30, 570, 780, 600); // BOT BORDER
//      rectangle(30, 540, 780, 550); // STATS-BOT BORDER

//      setfillstyle(SOLID_FILL, colors::DARKGRAY);
//      floodfill(1, 1, colors::DARKGRAY);    // Fill LEFT
//      floodfill(781, 1, colors::DARKGRAY);  // Fill RIGHT
//      floodfill(31, 1, colors::DARKGRAY);   // Fill TOP
//      floodfill(31, 571, colors::DARKGRAY); // Fill BOT
//      floodfill(31, 541, colors::DARKGRAY); // Fill STATS-BOT
// }
