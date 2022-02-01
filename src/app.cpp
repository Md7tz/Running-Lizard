/******************** Running Lizard Game ********************/
#include "GameManager/gameManager.h"

int main()
{
	WINBGI_H	::initwindow(WIDTH, HEIGHT, TITLE, CENTERX, CENTERY);
	GameManager ::initGame();
	WINBGI_H	::getch();
	WINBGI_H	::closegraph();
	return 0;
}