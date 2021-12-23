#ifndef POSITION_H
#define POSITION_H

#include <stdint.h>  	// Typedefs of fundamental integral types 

enum DIR
{
	LEFT, 	// 0
	UP,   	// 1
	RIGHT,	// 2
	DOWN  	// 3
};

class Position
{
public:
    int16_t x, y;
    Position();
    ~Position();
};

#endif