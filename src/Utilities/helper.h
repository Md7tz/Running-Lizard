inline void inputHandler(Lizard& body) {
	if (GetAsyncKeyState(VK_LEFT))
		body.changeDir(LEFT);
	if (GetAsyncKeyState(VK_UP))
		body.changeDir(UP);
	if (GetAsyncKeyState(VK_RIGHT))
		body.changeDir(RIGHT);
	if (GetAsyncKeyState(VK_DOWN))
		body.changeDir(DOWN);
	if (GetAsyncKeyState(VK_ESCAPE))
		exit(1);
}

// Generates new position if the position is equal to the food pos
inline void generationHandler(Edible& f, Poison& p, Lizard& b)
{
	if ((f.foodPos.x == p.foodPos.x && f.foodPos.y == p.foodPos.y))
	{
		p.generate(b.getPosX(), b.getPosY());
	}
}