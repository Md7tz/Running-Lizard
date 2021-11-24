enum DIR
{
	LEFT,
	UP,
	RIGHT,
	DOWN
}; // 0 1 2 3

struct Position
{
	int16_t x, y;
	Position()
	{
		x = 0;
		y = 0;
	}
};

class Lizard
{
protected:
	Position bodyPos[32]; // Contains the positions of the lizard
	uint8_t direction;
	uint8_t length;
	uint8_t offset;
	Rgb *rgb;

public:
	Lizard();
	~Lizard();

	void draw() const;
	void append();			   // Increments lizard length
	void changeDirTo(uint8_t); // Changes direction

	bool update();
	uint8_t getLength() const;

	int16_t getPosx() const;
	int16_t getPosy() const;

	const Position *getBody() const;
};

Lizard::Lizard()
{
	bodyPos[0].x = 30;	   // Initial x value for head
	bodyPos[0].y = 30;	   // Initial y value for head
	length = 2;		   // Initial length
	direction = RIGHT; // Initial direction
	offset = 30;	   // offset between object origin and x, y position
	rgb = new Rgb;	   // asign dynamic memory
}

Lizard::~Lizard() {}

void Lizard::draw() const
{ // Draws the lizard
	// Colors
	// 179, 170, 0
	// 245, 232, 0
	for (int i = 0; i < length; i++)
	{
		setcolor(YELLOW);
		rectangle(bodyPos[i].x, bodyPos[i].y, bodyPos[i].x + 30, bodyPos[i].y + 30);
		if (i == 0)
			setfillstyle(SOLID_FILL, COLOR(rgb->H[0], rgb->H[1], rgb->H[2])); // Head has a darker color than the body
		else
			setfillstyle(SOLID_FILL, COLOR(rgb->B[0], rgb->B[1], rgb->B[2]));
		floodfill(bodyPos[i].x + 15, bodyPos[i].y + 15, YELLOW);
	}
}

void Lizard::append()
{
	if (length < 33) // Prevents length from exceeding 32
		length++;
}

void Lizard::changeDirTo(uint8_t newdir)
{
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

bool Lizard::update()
{
	for (int8_t i = 1; i < length; ++i)
	{
		if (bodyPos[0].x == bodyPos[i].x && bodyPos[0].y == bodyPos[i].y)
		{
			return 0;
		}
	}
	for (int8_t i = length; i >= 0; --i)
	{
		if (i == 0)
		{
			bodyPos[1].x = bodyPos[0].x;
			bodyPos[1].y = bodyPos[0].y;
		}
		else
		{
			bodyPos[i].x = bodyPos[i - 1].x;
			bodyPos[i].y = bodyPos[i - 1].y;
		}
	}
	if (direction == LEFT)
	{
		bodyPos[0].x -= 30;
		if (bodyPos[0].x + offset == 0)
		{
			bodyPos[0].x = 780;
		}
	}
	else if (direction == RIGHT)
	{
		bodyPos[0].x += 30;
		if (bodyPos[0].x == 810)
		{
			bodyPos[0].x = 0;
		}
	}
	else if (direction == UP)
	{
		bodyPos[0].y -= 30;
		if (bodyPos[0].y + offset == 0)
		{
			bodyPos[0].y = 510;
		}
	}
	else if (direction == DOWN)
	{
		bodyPos[0].y += 30;
		if (bodyPos[0].y == 540)
		{
			bodyPos[0].y = 0;
		}
	}
	return true;
}

int16_t Lizard::getPosx() const
{
	return bodyPos[0].x;
}

int16_t Lizard::getPosy() const
{
	return bodyPos[0].y;
}

uint8_t Lizard::getLength() const
{
	return length;
}

const Position *Lizard::getBody() const
{
	return bodyPos;
}