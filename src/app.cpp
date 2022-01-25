/******************** Running Lizard Game ********************/
#include <graphics.h>	// Graphical user interface
#include <cstdint>  	// Typedefs of fundamental integral types 
#include <cstdlib>  	// String manipulation
#include <windows.h>    // Playing sounds
#include <cmath>		// Math functions

#include "Utilities/globals.h"

#ifndef ENV
	#define ENV 0 		// 0 == dev 
#endif
#if ENV == 0
	#define DEBUG true
#elif ENV == 1 			// 1 == prod
	#define DEBUG false
#endif

// Custom user defined Headers
#if DEBUG == true
	#include "Profiler/timer.h"
#endif
#include "Utilities/time.h"
#include "Utilities/position.h"
#include "Characters/lizard.h"
#include "Characters/player.h"
#include "Characters/enemy.h"
#include "GameObjects/menu.h"
#include "GameObjects/grid.h"
#include "GameObjects/food.h"
#include "GameObjects/edible.h"
#include "GameObjects/poison.h"

#include "GameManager/gameManager.h"

void update() {
	Menu* menu;
	Grid* grid;

	// Menu block
	G_MENU:
	menu = new Menu();
	while (!(menu->getGameState())) {
		#if DEBUG
			Timer timer;
		#endif
		menu->pagesHandler();
		menu->menuInputHandler();
		delay(100);
	}
	delete menu;

	// Start Block
	G_START:
	#pragma region Fields
	const int8_t fruitCount = Edible::getCount();
	
	// GameObjects
	Player player;
	Edible fruit[2] = { Edible(1), Edible(5) }; 	// Two Food objects initialized in a random position
	Poison poison;
	Enemy enemy(300, 300);

	int8_t page = 1;   		 						// Signed char  == int8_t | 1 byte | -128 to 127
	uint8_t bodyLength; 							// Unsigned char == uint8_t | 1 byte | 0 to 255
	uint8_t lifePadding = 0;						// Distance between the border of the heart and the center
	int16_t delayAmt = 90;							// The amount of delay between each frame to control the speed of the game
	int16_t lifeCount = 3; 							// Short int == int16_t | 2 bytes | -32,768 to 32,767

	bool skipFrame = true;							// Make the enemy skip a frame to reduce its speed to half the player's speed
	bool isPlaying = true;							// Status of the player
	bool revealEnemy = false; 						// blocks the enemy from instantiating , until the speed of lizard becomes insane
	bool collide = false;							// Checks if the player collided with the enemy and only changes after exiting the collision
	bool restart = false;							// Restarts the game if true

	char score[4] = "0";
	char speed[10] = "Normal";
#pragma endregion Fields

	// Generate new pos for food
	for (uint8_t i = 0; i < fruitCount; i++)
		fruit[i].generate(player.getPosx(), player.getPosy());

	// Generate new pos for poison
	poison.generate(player.getPosx(), player.getPosy());
	generationHandler(fruit[0], fruit[1], poison, player);

	while (true)
	{
		#if DEBUG == true
			Timer timer;
		#endif
		setup(page);

		// Create a grid in dynamic memory
		grid = new Grid();
		grid->draw();

		inputHandler(player, restart, isPlaying);
		collisionHandler(player, enemy, collide, skipFrame, revealEnemy, isPlaying, lifeCount);
		gameObjectsHandler(player, enemy, poison, fruit, isPlaying, revealEnemy, fruitCount);
		uiHandler(player, poison, fruit, bodyLength, score, speed, lifeCount, lifePadding, delayAmt, revealEnemy, isPlaying);

		// Checks game state
		if (restart) {
			cleardevice();
			goto G_START;
		};

		// Control speed between frames
		delay(delayAmt);

		// Free grid from memory
		delete grid;

		// Reset page
		page = 1 - page;
	}
}

int main()
{
	initwindow(WIDTH, HEIGHT, "Running Lizard", (getmaxwidth() - WIDTH) / 2, (getmaxheight() - HEIGHT) / 2);
	// PlaySound("Assets/SFX/background music .wav", NULL, SND_ASYNC);
	update();
	getch();
	closegraph();
	return 0;
}