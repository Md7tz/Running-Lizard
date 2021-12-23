#ifndef PLAYER_H
#define PLAYER_H

#include "lizard.h"

class Player : public Lizard
{
public:
	Player();
	~Player();

	void changeDir(uint8_t); // Changes direction
	void append();

	const Position* getBody() const;
};

#endif
