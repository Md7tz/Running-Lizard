#ifndef LIZARD_H
#define LIZARD_H

#include <cstdint>  	// Typedefs of fundamental integral types 
#include <graphics.h>
#include "../Utilities/position.h"
#include "../GameObjects/lives.h"



class Lizard
{
private:
	// composition
	// The lifetime of the position object is 
	// over when the lizard is destroyed in memory
	Position arr[31];
	// Aggregation
	Lives* lives;
	int direction;
	int length;

public:
	Lizard(Lives* lives)
	{
		arr[0].x = 30;     // Initial x value 
		arr[0].y = 30;     // Initial y value
		length = 2;        // Initial length
		direction = RIGHT; // Initial direction
		this->lives = lives;
	}
	void draw();
	void changeDir(int);
	int update();
	int getPosX();
	int getPosY();
	int getLength();
	Lives* getLivesADD();
	void drawLives();

};

#endif
