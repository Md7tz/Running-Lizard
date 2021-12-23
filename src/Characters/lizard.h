#ifndef LIZARD_H
#define LIZARD_H

#include <stdint.h>  	// Typedefs of fundamental integral types 
#include <graphics.h>	// Graphical user interface
#include "../Utilities/position.h"

class Lizard
{
protected:
    Position bodyPos[32];           // Contains the positions of the lizard
    uint8_t direction;
    uint8_t length;
    uint8_t offset = 30;            // offset between object origin and x, y position           
    int16_t H[3];                   // RGB color for lizard head
    int16_t B[3];                   // RGB color for lizard body
    uint8_t fillColor;

public:
    void draw() const;
    bool update();
    virtual void changeDir(uint8_t); // Changes direction

    uint8_t getLength() const;
    int16_t getPosx() const;
    int16_t getPosy() const;
};

#endif