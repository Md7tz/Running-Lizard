#pragma once

#ifndef ENV
	#define ENV 1 		// 0 == dev 
#endif
#if ENV == 0
	#define DEBUG true
#elif ENV == 1 			// 1 == prod
	#include <iostream>
	#define DEBUG false
#endif

#if DEBUG == true
	#include "Profiler/timer.h"
#endif

#include <graphics.h>	// Graphical user interface
#include <cstdint>  	// Typedefs of fundamental integral types 
#include <cstdlib>  	// String manipulation
#include <windows.h>    // Playing sounds
#include <cmath>		// Math functions

#include "../Utilities/globals.h"
#include "../Utilities/time.h"
#include "../Utilities/position.h"
#include "../Characters/lizard.h"
#include "../Characters/player.h"
#include "../Characters/enemy.h"
#include "../GameObjects/menu.h"
#include "../GameObjects/grid.h"
#include "../GameObjects/food.h"
#include "../GameObjects/edible.h"
#include "../GameObjects/poison.h"
#include "../GameObjects/lives.h"

#define TITLE "Running Lizard"
#define CENTERX (getmaxwidth() - WIDTH) / 2
#define CENTERY (getmaxwidth() - HEIGHT) / 2

class GameManager {
private:
    static Menu* menu;
    static Grid* grid;

    static Lives lives;
    static Player player;
    static Enemy enemy;
    static Edible fruit[2]; 	    // Two Food objects initialized in a random position
    static Poison poison;
 
    static int8_t page;             // Signed char  == int8_t | 1 byte | -128 to 127
    static uint8_t bodyLength;      // Unsigned char == uint8_t | 1 byte | 0 to 255
    static int16_t delayAmt;        // The amount of delay between each frame to control the speed of the game
    static int16_t lifeCount;       // Short int == int16_t | 2 bytes | -32,768 to 32,767
    static int8_t fruitCount;

    static bool skipFrame;			// Make the enemy skip a frame to reduce its speed to half the player's speed
    static bool isPlaying;			// Status of the player
    static bool revealEnemy; 		// blocks the enemy from instantiating , until the speed of lizard becomes insane
    static bool collide;			// Checks if the player collided with the enemy and only changes after exiting the collision
    static bool restart;			// Restarts the game if true

    static char score[4];
    static char speed[10];

    static void setup();
    static void setAll();
    static void generationHandler();
    static void inputHandler();
    static void collisionHandler();
    static void uiHandler();
    static void gameObjectsHandler();

public:
    static void initGame();
};