#ifndef PLAYER_H
#define PLAYER_H

#include "lizard.h"

class Player : public Lizard
{
private:
	Lives* lives;
public:
	Player(Lives* lives=NULL);
	~Player();

	void changeDir(uint8_t); // Changes direction
	void append();

	const Position* getBody() const;
};

#endif
