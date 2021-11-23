enum DIR { LEFT, UP, RIGHT, DOWN }; // 0 1 2 3

struct Position {
	int16_t x, y;
	Position()
	{
		x = -50;
		y = 0;
	}
};

class Lizard
{
private:
	Position arr[32];            	  // Contains the positions of the lizard
	uint8_t direction;
	uint8_t length;
	uint8_t offset;
	Rgb* rgb;

public:
	Lizard();
	~Lizard();

	void draw() const;
	void append();              // Increments lizard length
	void changeDirTo(uint8_t);        // Changes direction 

	uint8_t update();
	uint8_t getLength() const;

	int16_t getPosx() const;
	int16_t getPosy() const;
};

Lizard::Lizard() {
	arr[0].x = 30;        // Initial x value for head
	arr[0].y = 30;        // Initial y value for head
	length = 2;           // Initial length
	direction = RIGHT;    // Initial direction
	offset = 30;          // offset between object origin and x, y position
	rgb = new Rgb;		  // asign dynamic memory
}

Lizard::~Lizard() {
	// delete rgb;
}

void Lizard::draw() const {    // Draws the lizard
	// Colors
	// 179, 170, 0
	// 245, 232, 0
	for (int i = 0; i < length; i++)
	{
		setcolor(YELLOW);
		rectangle(arr[i].x, arr[i].y, arr[i].x + 30, arr[i].y + 30);
		if (i == 0)
			setfillstyle(SOLID_FILL, COLOR(rgb->H[0], rgb->H[1], rgb->H[2])); // Head has a darker color than the body
		else
			setfillstyle(SOLID_FILL, COLOR(rgb->B[0], rgb->B[1], rgb->B[2]));
		floodfill(arr[i].x + 15, arr[i].y + 15, YELLOW);
	}
}

void Lizard::append() {
	if (length < 33)  // Prevents length from exceeding 32
		length++;
}

void Lizard::changeDirTo(uint8_t newdir) {
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

uint8_t Lizard::update() {
	for (int8_t i = 1; i < length; ++i)
	{
		if (arr[0].x == arr[i].x && arr[0].y == arr[i].y)
		{
			return 0;
		}
	}
	for (int8_t i = length; i >= 0; --i)
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

int16_t Lizard::getPosx() const
{
	return arr[0].x;
}

int16_t Lizard::getPosy() const
{
	return arr[0].y;
}

uint8_t Lizard::getLength() const
{
	return length;
}