#include <graphics.h>

enum DIR { LEFT, UP, RIGHT, DOWN }; // 0 1 2 3

struct Position {
	short int x, y;
	Position()
	{
		x = -50;
		y = 0;
	}
};

class LizardBody
{
private:
	Position arr[32];            // Contains the positions of the lizard
	unsigned char direction;
	unsigned char length;
	unsigned char offset;

public:
	LizardBody()
	{
		arr[0].x = 30;        // Initial x value for head
		arr[0].y = 30;        // Initial y value for head
		length = 2;           // Initial length
		direction = RIGHT;    // Initial direction
		offset = 30;          // offset between object origin and x, y position
	}
	void drawLizard() const;
	void appendLizard();                    // Increments lizard length
	void changeDirTo(unsigned char);        // Changes direction 

	unsigned char update();
	unsigned char getlength() const;

	short int getPosx() const;
	short int getPosy() const;
};
void LizardBody::drawLizard() const {    // Draws the lizard
	// Colors
	// 179, 170, 0
	// 245, 232, 0
	for (int i = 0; i < length; i++)
	{
		setcolor(YELLOW);
		rectangle(arr[i].x, arr[i].y, arr[i].x + 30, arr[i].y + 30);
		if (i == 0)
			setfillstyle(SOLID_FILL, COLOR(179, 170, 0)); // Head has a darker color than the body
		else
			setfillstyle(SOLID_FILL, COLOR(245, 232, 0));
		floodfill(arr[i].x + 15, arr[i].y + 15, YELLOW);
	}
}

void LizardBody::appendLizard() {
	if (length < 33)  // Prevents length from exceeding 32
		length++;
}

void LizardBody::changeDirTo(unsigned char newdir) {
	if (newdir == LEFT || newdir == RIGHT)
	{
		if (direction == UP || direction == DOWN)
			direction = newdir;
	}
	else if (newdir == UP || newdir == DOWN)
	{
		if (direction == LEFT || direction == RIGHT)
			direction = newdir;
	}
}

unsigned char LizardBody::update() {
	for (signed char i = 1; i < length; ++i)
	{
		if (arr[0].x == arr[i].x && arr[0].y == arr[i].y)
		{
			return 0;
		}
	}
	for (signed char i = length; i >= 0; --i)
	{
		if (i == 0)
		{
			arr[1].x = arr[0].x;
			arr[1].y = arr[0].y;
		}
		else
		{
			arr[i].x = arr[i - 1].x;
			arr[i].y = arr[i - 1].y;
		}
	}
	if (direction == LEFT)
	{
		arr[0].x -= 30;
		if (arr[0].x + offset == 0)
		{
			arr[0].x = 780;
		}
	}
	else if (direction == RIGHT)
	{
		arr[0].x += 30;
		if (arr[0].x == 810)
		{
			arr[0].x = 0;
		}
	}
	else if (direction == UP)
	{
		arr[0].y -= 30;
		if (arr[0].y + offset == 0)
		{
			arr[0].y = 510;
		}
	}
	else if (direction == DOWN)
	{
		arr[0].y += 30;
		if (arr[0].y == 540)
		{
			arr[0].y = 0;
		}
	}
	return 1;
}

short int LizardBody::getPosx() const
{
	return arr[0].x;
}

short int LizardBody::getPosy() const
{
	return arr[0].y;
}

unsigned char LizardBody::getlength() const
{
	return length;
}