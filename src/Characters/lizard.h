#ifndef LIZARD_H
#define LIZARD_H

#include <cstdint>  	// Typedefs of fundamental integral types 
#include <graphics.h>
#include "../Utilities/position.h"

class Lizard
{
private:
	Position arr[31];
	int direction;
	int length;

public:
	Lizard()
	{
		arr[0].x = 30;     // Initial x value 
		arr[0].y = 30;     // Initial y value
		length = 2;        // Initial length
		direction = RIGHT; // Initial direction
	}
	void draw();
	void changeDir(int);
	int update();
	int getPosX();
	int getPosY();
	int getLength();
};

#endif
