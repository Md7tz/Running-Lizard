/*----------Running lizard GAME----------*/

#include <graphics.h>
// #include <windows.h> for playing sounds
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include "lizardBody.h"
#include "food.h"
#include "poison.h"

// #pragma comment(lib, "winmm.lib")

#define WIDTH 810
#define HEIGHT 600
using namespace std;

// Drawing Screen
void drawGrid();
void drawKeys(int16_t, int16_t);
void drawLives(const uint8_t, uint8_t&);
void drawInstruction(int16_t, int16_t, int16_t, int16_t);

// Utility Function
inline void GenerationHandler(Food, Food, Poison, LizardBody);

int main() {
	initwindow(WIDTH, HEIGHT, "Running Lizard");
start:
	LizardBody body;
	Food fruit[2] = { Food(1), Food(5) }; // Two Food objects initialized by passing an int to the constructor
	Poison p1;

#pragma region Fields
	// unsigned char == uint8_t | 1 byte | 0 to 255
	// signed char  == int8_t | 1 byte | -128 to 127
	// short int == int16_t | 2 bytes | -32,768 to 32,767
	int8_t page = 1;
	uint8_t bodyLength;
	uint8_t delaySpeed = 90;
	uint8_t lifeCount = 3;
	uint8_t lifePadding = 0;
	const int8_t fruitCount = fruit[0].getCount();

	char score[4] = "0";
	char speed[10] = "Normal";

	bool isPlaying = true;
#pragma endregion Fields

	// generate new pos for food
	for (uint8_t i = 0; i < fruitCount; i++)
		fruit[i].generate(body.getPosx(), body.getPosy());

	// generate/regenerate new pos for poison
	p1.generate(body.getPosx(), body.getPosy());
	GenerationHandler(fruit[0], fruit[1], p1, body);

	while (true)
	{
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();

		setcolor(BLUE);
		setfillstyle(SOLID_FILL, BLUE);

		// Input Handler
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
			body.changeDirTo(LEFT);
		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
			body.changeDirTo(UP);
		if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
			body.changeDirTo(RIGHT);
		if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
			body.changeDirTo(DOWN);
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
		if (GetAsyncKeyState('R'))
			goto start;
		if (isPlaying == true && !body.update())
			isPlaying = false;

		/*-UI-*/
		drawGrid();
		body.drawLizard();

		for (uint8_t i = 0; i < fruitCount; i++)
		{
			if (fruit[i].update(body.getPosx(), body.getPosy()))
			{
				fruit[i].generate(body.getPosx(), body.getPosy());
				// bool played = PlaySound(TEXT("DieSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
				// cout << boolalpha << played << endl;
				body.appendLizard();
			}
		}

		// Score
		settextstyle(font_names::SANS_SERIF_FONT, HORIZ_DIR, 1);
		setcolor(WHITE);

		// Calculate score from body length
		bodyLength = body.getlength();
		strncpy(score, to_string((bodyLength - 2) * 10).c_str(), 4);

		// Display score
		outtextxy(20, 545, (char*)"SCORE");
		outtextxy(90, 545, score);

		// Game State
		// Regenerate new poison position
		// Check if player ate 3 poison
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
		if (p1.update(body.getPosx(), body.getPosy()))
		{
			p1.generate(body.getPosx(), body.getPosy());
			GenerationHandler(fruit[0], fruit[1], p1, body);
			lifeCount--;
			if (p1.getHit() == 3)
			{
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
				outtextxy(160, 545, (char*)"GAME OVER");
				isPlaying = false;
			}
		}
		else if (isPlaying)
		{
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
			outtextxy(160, 545, (char*)"PLAYING");
		}

		// Display Controls - WASD
		setcolor(WHITE);
		drawKeys(295, 545);

		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
		outtextxy(295, 545, (char*)" W ");
		outtextxy(270, 568, (char*)" A  ");
		outtextxy(295, 568, (char*)" S  ");
		outtextxy(320, 568, (char*)" D  ");


		// Display Controls - Arrow Keys
		setcolor(BLACK);
		drawKeys(385, 545);
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

		// Display Speed
		setcolor(WHITE);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
		outtextxy(20, 575, (char*)"Speed");
		outtextxy(90, 575, speed);

		// Draw lives
		drawLives(lifeCount, lifePadding);

		// Draw food
		for (uint8_t i = 0; i < fruitCount; i++)
			fruit[i].draw();

		// Draw poison
		p1.draw();

		// Reset page
		page = 1 - page;

		// Display Exit Key
		setcolor(WHITE);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
		outtextxy(630, 545, (char*)" PRESS 'ESC' to EXIT ");

		// Draw instruction
		drawInstruction(680, 575, 20, 90);

		// Check if player reached max length -> Won
		if (body.getlength() == 32)
		{
			setcolor(WHITE);
			outtextxy(160, 545, (char*)"Victory!");
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
			outtextxy(155, 200, (char*)"You Won! Press R to Restart");
			isPlaying = false;
		}
		// Retry prompt
		if (!isPlaying && body.getlength() != 32)
		{
			setcolor(WHITE);
			outtextxy(160, 545, (char*)"GAME OVER");
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
			outtextxy(250, 200, (char*)" Press R to Retry ");
		}

		// Control speed between frames
		delay(delaySpeed);
	}

	getch();
	closegraph();
}

#pragma region Functions
// Draw Box Grid with texture
void drawGrid()
{
	uint8_t size = 30; // box size in grid
	int16_t left = 0, top = 0, right = 30, bottom = 30;
	int16_t x = 5, y = 5;
	uint8_t i = 0;

	// Color A: 229 255 204
	// Color B: 204 255 204

	// fill background with color first
	setfillstyle(fill_styles::SOLID_FILL, COLOR(204, 255, 204));
	floodfill(x, y, COLOR(204, 255, 204));

	// Divide background to grid containers and fill with color
	setcolor(COLOR(229, 255, 204));
	for (uint8_t row = 0; row < HEIGHT / size; row++)
	{
		for (uint8_t col = 0; col < WIDTH / size; col++)
		{
			rectangle(left, top, right, bottom);
			left += size;
			right += size;
			if (i % 2 == 0)
			{
				setfillstyle(fill_styles::SOLID_FILL, COLOR(229, 255, 204));
				floodfill(x, y, COLOR(229, 255, 204));
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
}

// Draw key boxes
void drawKeys(int16_t x, int16_t y)
{
	for (int16_t i = 0; i < 4; i++)
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

// Draw lives left
void drawLives(const uint8_t counter, uint8_t& padding)
{
	uint8_t temp = padding;
	setcolor(RED);
	for (uint8_t j = 0; j < 3; j++) {
		arc(485 + padding, 555, 0, 180, 10);
		arc(465 + padding, 555, 0, 180, 10);
		arc(475 + padding, 555, 180, 360, 20);
		padding += 50;
	}
	padding = temp;
	for (uint8_t i = 0; i < counter; i++)
	{
		setfillstyle(SOLID_FILL, RED);
		floodfill(475 + padding, 560, RED);
		padding += 50;
	}
	padding = 0;
}

// Draw instructions
void drawInstruction(int16_t x, int16_t y, int16_t size, int16_t offset) {
	// Text
	setcolor(COLOR(255, 45, 0));
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	outtextxy(630, 575, (char*)"FOOD");
	// Food
	setcolor(RED);
	rectangle(x, y, x + size, y + size);
	setfillstyle(INTERLEAVE_FILL, RED);
	floodfill(x + (size / 2), y + (size / 2), RED);
	// Text
	setcolor(COLOR(10, 255, 0));
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	outtextxy(705, 575, (char*)"POISON");
	// Poison
	setcolor(GREEN);
	rectangle(x + offset, y, x + size + offset, y + size);
	setfillstyle(INTERLEAVE_FILL, GREEN);
	floodfill(x + (size / 2) + offset, y + (size / 2), GREEN);
}

// Using inline solves overhead costs. It is expanded in line by the compiler when it is invoked.
// Generates new position if the position 
// is equal to the food pos
inline void GenerationHandler(Food f1, Food f2, Poison p1, LizardBody b)
{
	if ((f1.foodPos.x == p1.foodPos.x && f1.foodPos.y == p1.foodPos.y) ||
		(f2.foodPos.x == p1.foodPos.x && f2.foodPos.y == p1.foodPos.y))
	{
		p1.generate(b.getPosx(), b.getPosy());
	}
}
#pragma endregion Functions
