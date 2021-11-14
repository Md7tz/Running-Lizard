/*----------Running lizard GAME----------*/

#include <graphics.h>
#include <stdlib.h>
#include <iostream>
#include "lizardBody.h"
#include "food.h"
#include "poison.h"

// void drawBorders();
void drawGrid();
void drawKeys(int, int); // draw 4 keys
void drawLives(const int, int&);
void avoidConflict(Food f1, Food f2, poison p3, LizardBody b);

using namespace std;

const int WIDTH = 810;
const int HEIGHT = 600;

int main()
{
     initwindow(WIDTH, HEIGHT, "Running Lizard");

start:
     LizardBody body;
     Food fruit[2] = { Food(1), Food(5) };
     poison p1(3);

     int length, count = 0;
     int page = 0;
     int delaySpeed = 90;
     int lifeCount = 3;
     int lifePadding = 0;
     const int fruitCount = fruit[0].getCount();

     char score[4] = "0";
     char speed[10] = "Normal";

     bool playing = true;

     for (int i = 0; i < fruitCount; i++)
     {
          fruit[i].generate(body.getPosx(), body.getPosy());
     }
     p1.generate(body.getPosx(), body.getPosy());
     avoidConflict(fruit[0], fruit[1], p1, body);
     // cout << "test";

     while (true)
     {
          setactivepage(page);
          setvisualpage(1 - page);
          cleardevice();

          setcolor(BLUE);
          setfillstyle(SOLID_FILL, BLUE);

          if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41))
          {
               body.changeDirTo(LEFT);
          }
          if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x57))
          {
               body.changeDirTo(UP);
          }
          if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44))
          {
               body.changeDirTo(RIGHT);
          }
          if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(0x53))
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

          /*-UI-*/
          // drawBorders();
          drawGrid();
          body.drawLizard();

          for (int i = 0; i < fruitCount; i++)
          {
               if (fruit[i].update(body.getPosx(), body.getPosy()))
               {
                    fruit[i].generate(body.getPosx(), body.getPosy());
                    body.appendLizard();
                    // fruits[i].getCount()--;
               }
          }
          // SCORE
          settextstyle(font_names::SANS_SERIF_FONT, HORIZ_DIR, 1);
          setcolor(WHITE);

          length = body.getlength();
          strncpy(score, to_string((length - 2) * 10).c_str(), 4);

          outtextxy(20, 545, (char*)"SCORE");
          outtextxy(90, 545, score);

          // STATUS
          settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
          // outtextxy(520, 300, "STATUS :-");
          if (p1.update(body.getPosx(), body.getPosy()))
          {
               p1.generate(body.getPosx(), body.getPosy());
               avoidConflict(fruit[0], fruit[1], p1, body);
               lifeCount--;
               if (p1.getHit() == 3)
               {
                    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
                    outtextxy(160, 545, (char*)"GAME OVER");
                    playing = false;
               }
          }
          if (body.getlength() == 32)
          {
               outtextxy(160, 545, (char*)"Victory!");
               settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
               outtextxy(155, 200, (char*)"You Won! Press R to Restart");
               playing = false;
          }
          else if (playing)
          {
               outtextxy(160, 545, (char*)"PLAYING");
          }
          else
          {
               outtextxy(160, 545, (char*)"GAME OVER");
               settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
               outtextxy(245, 200, (char*)"Press R to Retry");
          }

          // Controls - WASD
          setcolor(GREEN);
          drawKeys(295, 543);

          settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
          outtextxy(295, 543, (char*)" W ");
          outtextxy(270, 568, (char*)" A  ");
          outtextxy(295, 568, (char*)" S  ");
          outtextxy(320, 568, (char*)" D  ");

          setcolor(GREEN);
          drawKeys(385, 543);

          setcolor(BLACK);
          // up arrow key
          line(388, 559, 395, 549);
          line(395, 549, 402, 559);
          // down arrow key
          line(388, 574, 395, 584);
          line(395, 584, 402, 574);
          // right arrow key
          line(415, 574, 428, 579);
          line(428, 579, 416, 584);
          // left arrow key
          line(378, 574, 365, 579);
          line(365, 579, 378, 584);
          setcolor(WHITE);

          // Controls - Arrows
          settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
          outtextxy(640, 545, (char*)"PRESS 'ESC' to EXIT");

          // Progressive speed
          if (atoi(score) >= 100)
          {
               delaySpeed = 40;
               strcpy(speed, "Fast");
          }
          if (atoi(score) >= 200)
          {
               delaySpeed = 25;
               strcpy(speed, "Insane");
          }
          // else {
          //      delaySpeed = 50;
          //      strcpy(speed, "Normal");
          // }

          outtextxy(20, 575, (char*)"Speed");
          outtextxy(90, 575, speed);

          // Draw lives
          drawLives(lifeCount, lifePadding);

          for (int i = 0; i < fruitCount; i++)
               fruit[i].draw();
          // if (playing)
          p1.draw();
          // fruits[0].getCount();
          page = 1 - page;
          delay(delaySpeed);
          // cout << delaySpeed << endl;
          // cout << score << endl;
          // cout << speed << endl;
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

// Draw Box Grid with texture
void drawGrid()
{
     int size = 30; // box size in grid
     int left = 0, top = 0, right = 30, bottom = 30;
     int x = 5, y = 5;
     int i = 0;

     // Color A: 229 255 204
     // Color B: 204 255 204

     // fill background with color first
     setfillstyle(fill_styles::SOLID_FILL, COLOR(204, 255, 204));
     floodfill(x, y, COLOR(204, 255, 204));

     // Divide background to grid containers and fill with color
     setcolor(COLOR(229, 255, 204));
     for (int row = 0; row < HEIGHT / size; row++)
     {
          for (int col = 0; col < WIDTH / size; col++)
          {
               rectangle(left, top, right, bottom);
               left += size;
               right += size;
               if (i % 2 == 0)
               {
                    setfillstyle(fill_styles::SOLID_FILL, COLOR(229, 255, 204));
                    floodfill(x, y, COLOR(229, 255, 204));
               }
               // refactored for optimization
               // else
               // {
               //      setcolor(COLOR(204, 255, 204));
               //      setfillstyle(fill_styles::SOLID_FILL, COLOR(204, 255, 204));
               //      floodfill(x, y, COLOR(204, 255, 204));
               // }
               x += 30;
               i++;
          }
          left = 0;
          right = size;
          top += size;
          bottom += size;
          x = 5;
          y += 30;
     }
     // cout << "grid ready";
     // gridDrawn = true;
}

// Draw key boxes
void drawKeys(int x, int y)
{
     for (int i = 0; i < 4; i++)
     {
          rectangle(x, y, x + 22, y + 20);
          if (i == 0)
          {
               y += 25;
               x -= 50;
          }
          x += 25;
     }
}

void drawLives(const int counter, int& padding)
{
     setcolor(RED);
     for (int i = 0; i < counter; i++)
     {
          arc(500 + padding, 555, 0, 180, 10);
          arc(480 + padding, 555, 0, 180, 10);
          arc(490 + padding, 555, 180, 360, 20);
          setfillstyle(SOLID_FILL, RED);
          floodfill(490 + padding, 560, RED);
          padding += 50;
     }
     padding = 0;
}
void avoidConflict(Food f1, Food f2, poison p1, LizardBody b)
{
     if ((f1.foodPos.x == p1.foodPos.x && f1.foodPos.y == p1.foodPos.y) ||
          (f2.foodPos.x == p1.foodPos.x && f2.foodPos.y == p1.foodPos.y))
     {
          p1.generate(b.getPosx(), b.getPosy());
     }

}
