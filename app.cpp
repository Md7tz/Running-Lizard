/*----------Running lizard GAME----------*/

#include <graphics.h>
#include <iostream>
#include "lizardBody.h"
#include "food.h"
#include "poison.h"

// void drawBorders();
void drawGrid();
void draw_4_key(int x, int y); // draw 4 keys

using namespace std;

const int WIDTH = 810;
const int HEIGHT = 600;

int main()
{
     initwindow(WIDTH, HEIGHT, "Running Lizard");

start:
     LizardBody body;
     Food fruit;
     int length, count = 0;
     bool playing = true;
     char score[4];
     char fpsCounter[4];
     int page = 0;

     fruit.generate(body.getPosx(), body.getPosy());

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

          // UI
          // drawBorders();
          drawGrid();
          body.drawLizard();

          if (fruit.update(body.getPosx(), body.getPosy()))
          {
               fruit.generate(body.getPosx(), body.getPosy());
               body.appendLizard();
          }

          // SCORE
          settextstyle(font_names::SANS_SERIF_FONT, HORIZ_DIR, 1);
          setcolor(WHITE);

          length = body.getlength();
          strncpy(score, to_string((length - 2) * 10).c_str(), 4);

          outtextxy(50, 545, (char*)"SCORE");
          outtextxy(120, 545, score);

          // STATUS
          settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
          // outtextxy(520, 300, "STATUS :-");
          if (body.getlength() == 32)
          {
               outtextxy(160, 545, (char*)"YOU WON !");
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
               outtextxy(250, 200, (char*)"Press R to Retry");
          }

          // Controls - WASD
          setcolor(GREEN);
          draw_4_key(295, 538);

          settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
          outtextxy(295, 538, (char*)" W ");
          outtextxy(270, 563, (char*)" A  ");
          outtextxy(295, 563, (char*)" S  ");
          outtextxy(320, 563, (char*)" D  ");

          setcolor(GREEN);
          draw_4_key(385, 538);

          setcolor(BLACK);
          // up arrow key
          line(388, 553, 395, 543);
          line(395, 543, 402, 553);
          // down arrow key
          line(388, 568, 395, 578);
          line(395, 578, 402, 568);
          // right arrow key
          line(415, 568, 428, 573);
          line(428, 573, 416, 578);
          // left arrow key
          line(378, 568, 365, 573);
          line(365, 573, 378, 578);
          setcolor(WHITE);

          // Controls - Arrows
          settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
          outtextxy(580, 545, (char*)"PRESS 'ESC' to EXIT");

          fruit.draw();
          page = 1 - page;
          delay(100);
     }

     // fps.update();
     // settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
     // strncpy(fpsCounter, to_string(fps.get()).c_str(), 4);
     // outtextxy(30, 30, fpsCounter);

     getch();
     closegraph();
}

// Initial state grid with no borders
void drawBorders()
{
     setcolor(DARKGRAY);
     rectangle(0, 0, 30, 600);     // LEFT BORDER
     rectangle(780, 0, 810, 610);  // RIGHT BORDER
     rectangle(30, 0, 780, 30);    // TOP BORDER
     rectangle(30, 570, 780, 600); // BOT BORDER
     rectangle(30, 540, 780, 550); // STATS-BOT BORDER

     setfillstyle(SOLID_FILL, colors::DARKGRAY);
     floodfill(1, 1, colors::DARKGRAY);    // Fill LEFT
     floodfill(781, 1, colors::DARKGRAY);  // Fill RIGHT
     floodfill(31, 1, colors::DARKGRAY);   // Fill TOP
     floodfill(31, 571, colors::DARKGRAY); // Fill BOT
     floodfill(31, 541, colors::DARKGRAY); // Fill STATS-BOT
}

// Draw Box Grid with texture
void drawGrid()
{
     int size = 30; // box size in grid
     int left = 0, top = 0, right = 30, bottom = 30;
     int x = 5, y = 5;
     int i = 0;

     // Color A: 229 255 204
     // Color B: 204 255 204

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
               else
               {
                    setcolor(COLOR(204, 255, 204));
                    setfillstyle(fill_styles::SOLID_FILL, COLOR(204, 255, 204));
                    floodfill(x, y, COLOR(204, 255, 204));
               }
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
void draw_4_key(int x, int y)
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