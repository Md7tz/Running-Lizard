class Player : public Lizard
{
public:
	Player();
	~Player();

	void changeDir(uint8_t); // Changes direction
	void append();

	const Position* getBody() const;
};

Player::Player()
{
	bodyPos[0].x = 30;	   // Initial x value for head
	bodyPos[0].y = 30;	   // Initial y value for head
	length = 2;		   // Initial length
	direction = RIGHT; // Initial direction
	H[0] = 179; H[1] = 170; H[2] = 0;
    B[0] = 245; B[1] = 232; B[2] = 0;
	fillColor = YELLOW;
}

Player::~Player() {}

void Player::changeDir(uint8_t newdir)
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

void Player::append()
{
	if (length < 33) // Prevents length from exceeding 32
		length++;
}

const Position* Player::getBody() const
{
	return bodyPos;
}