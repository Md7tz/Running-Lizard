/*----------Running lizard GAME----------*/

#include <graphics.h>
#include <stdint.h>  	// For typedefs of fundamental integral types 
#include <stdlib.h>  	// For string manipulation
#include <iostream>  	// For debugging
#include <ctime> 	 	// For Generating random numbers

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
#include "Utilities/position.h"
#include "Characters/lizard.h"
#include "Characters/player.h"
#include "Characters/enemy.h"
#include "GameObjects/grid.h"
#include "GameObjects/food.h"
#include "GameObjects/edible.h"
#include "GameObjects/poison.h"

using namespace std;

// Drawing Screen UI
void drawKeys(int16_t, int16_t);
void drawLives(const int16_t, uint8_t&);
void drawInstruction(int16_t, int16_t, int16_t, int16_t);

// Utility Functions
inline void setup(int8_t&);
inline void GenerationHandler(Edible&, Edible&, Poison&, Player&);
inline void inputHandler(Player&, Enemy&, bool&, bool&, bool&);
void collisionHandler(Player&, Enemy&, bool&, bool&, bool&, bool&, int16_t&);
void uiHandler(Player&, Poison&, Edible[2], uint8_t&, char[4], char[10], int16_t&, uint8_t&, int16_t&, bool&, bool&);
void gameObjectsHandler(Player&, Enemy&, Poison&, Edible[], bool&, bool&, int8_t);

int main()
{
	initwindow(WIDTH, HEIGHT, "Running Lizard");

start:
#pragma region Fields
	Grid* grid;
	Player player;
	Edible fruit[2] = { Edible(1), Edible(5) }; 	// Two Food objects initialized in a random position
	Poison poison;
	Enemy enemy(300, 300);

	uint8_t bodyLength; 							// unsigned char == uint8_t | 1 byte | 0 to 255
	uint8_t lifePadding = 0;
	const int8_t fruitCount = fruit[0].getCount();
	int8_t page = 1;   		 						// signed char  == int8_t | 1 byte | -128 to 127
	int16_t delaySpeed = 90;
	int16_t lifeCount = 3; 							// short int == int16_t | 2 bytes | -32,768 to 32,767

	bool revealEnemy = false; 						// will not show enemy , unitil the speed of lizard be insane
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
	GenerationHandler(fruit[0], fruit[1], poison, player);

	while (true)
	{
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

	getch();
	closegraph();
}

#include "GameManager/gameManager.h"