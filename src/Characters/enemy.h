#ifndef ENEMY_H
#define ENEMY_H

#include <ctime>
#include "lizard.h"
#include "player.h"

class Enemy : public Lizard
{
public:
    Enemy(int16_t x=0, int16_t y=0);
    ~Enemy();
    
    bool checkBody(Player& body);
    void changeDir(uint8_t = 0);
};

#endif