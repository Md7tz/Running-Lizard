/******************** Running Lizard Game ********************/
#include <graphics.h>	// Graphical user interface
#include <stdint.h>  	// Typedefs of fundamental integral types 
#include <stdlib.h>  	// String manipulation
#include <iostream>  	// Debugging
#include <ctime> 	 	// Generating random numbers
#include <windows.h>    // Playing sounds
#include <chrono>		// Time
#include <cmath>		

// Preprocessor definitions
#define WIDTH 810
#define HEIGHT 600

enum DIR
{
	LEFT,
	UP,
	RIGHT,
	DOWN
}; 						// 0 1 2 3

// Custom user defined Headers
#include "Profiler/timer.h"
#include "Utilities/time.h"
#include "Utilities/position.h"
#include "Characters/lizard.h"
#include "Characters/player.h"
#include "Characters/enemy.h"
#include "GameObjects/grid.h"
#include "GameObjects/food.h"
#include "GameObjects/edible.h"
#include "GameObjects/poison.h"
#include "GameManager/gameManager.h"

void fixedUpdate() { // runs a frame every 0.02 so every min 50 frames are gone by
start:
#pragma region Fields
	Grid* grid;
	Player player;
	Edible fruit[2] = { Edible(1), Edible(5) }; 	// Two Food objects initialized in a random position
	Poison poison;
	Enemy enemy(300, 300);

	const int8_t fruitCount = fruit[0].getCount();
	int8_t page = 1;   		 						// signed char  == int8_t | 1 byte | -128 to 127
	uint8_t bodyLength; 							// unsigned char == uint8_t | 1 byte | 0 to 255
	uint8_t lifePadding = 0;
	int16_t delaySpeed = 90;
	int16_t lifeCount = 3; 							// short int == int16_t | 2 bytes | -32,768 to 32,767

	bool revealEnemy = false; 						// Will not show enemy , until the speed of lizard be insane
	bool collide = false;
	bool skipFrame = true;
	bool isPlaying = true;
	bool exit = false;
	bool restart = false;

	char score[4] = "0";
	char speed[10] = "Normal";
#pragma endregion Fields

	// generate new pos for food
	for (uint8_t i = 0; i < fruitCount; i++)
		fruit[i].generate(player.getPosx(), player.getPosy());

	// generate new pos for poison
	poison.generate(player.getPosx(), player.getPosy());
	generationHandler(fruit[0], fruit[1], poison, player);

	// uint64_t lastTime = CurrentTime_nanoseconds();
	// const double ns = 1000000000.0 / 60.0;
	// double delta = 0;
	while (true)
	{
		// uint64_t now = CurrentTime_nanoseconds();
		// std::cout << lastTime << std::endl << now << '\n';
		// return;
		Timer timer;
		setup(page);

		// Create a grid in dynamic memory
		grid = new Grid();
		grid->draw();

		inputHandler(player, enemy, exit, restart, isPlaying);
		collisionHandler(player, enemy, collide, skipFrame, revealEnemy, isPlaying, lifeCount);
		gameObjectsHandler(player, enemy, poison, fruit, isPlaying, revealEnemy, fruitCount);
		uiHandler(player, poison, fruit, bodyLength, score, speed, lifeCount, lifePadding, delaySpeed, revealEnemy, isPlaying);

		// Checks game state
		if (exit) break;
		else if (restart) goto start;

		// Control speed between frames
		delay(delaySpeed);


		// Free grid from memory
		delete grid;
		grid = NULL;

		// Reset page
		page = 1 - page;
	}
}

int main()
{
	PlaySound("Assets/SFX/background music .wav", NULL, SND_ASYNC);
	initwindow(WIDTH, HEIGHT, "Running Lizard");
	std::cout << CurrentTime_nanoseconds() << 1000000000.0 << std::endl;
	fixedUpdate();
	getch();
	closegraph();
	return 0;
}