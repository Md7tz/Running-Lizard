class Enemy : public Lizard
{
public:
    Enemy(int16_t x, int16_t y);
    // ~Enemy();
    bool checkBody(Player& body);
    void changeDir();
};

Enemy::Enemy(int16_t x, int16_t y)
{
    bodyPos[0].x = x;      // Initial x value for head
    bodyPos[0].y = y;      // Initial y value for head
    length = 2;        // Initial length
    direction = RIGHT; // Initial direction
    H[0] = 0; H[1] = 0; H[2] = 0;
    B[0] = 66; B[1] = 67; B[2] = 69;
    fillColor = BLACK;
}

// Enemy::~Enemy() {}


bool Enemy::checkBody(Player& body)
{ // to check that there is no collosion between the two bodys
    int16_t bodyLength = body.getLength();
    for (int i = 0; i < bodyLength; i++) {
        for (int x = 0; x < length; ++x)
            if (body.getBody()[i].x == bodyPos[x].x && body.getBody()[i].y == bodyPos[x].y)
                return false;
    }
    return true;
}

void Enemy::changeDir()
{
    // Generate a random number in range from 0-3 direction for the enemy lizard
    srand(time(NULL));
    int tempDir = (rand() % 3) + 1;

    // Avoid invalid directions
    if (tempDir == LEFT || tempDir == RIGHT)
    {
        if (!(direction == UP || direction == DOWN))
            return;
        direction = tempDir;
    }
    else if (tempDir == UP || tempDir == DOWN)
    {
        if (!(direction == LEFT || direction == RIGHT))
            return;
        direction = tempDir;
    }
}