
class Enemy : public Lizard
{
public:
    Enemy(int16_t x, int16_t y);
    int8_t checkBody(Lizard& body);
    void draw() const;
    void append(Lizard&);
    void changeDir();
};

Enemy::Enemy(int16_t x, int16_t y)
{
    arr[0].x = x;      // Initial x value for head
    arr[0].y = y;      // Initial y value for head
    length = 2;        // Initial length
    direction = RIGHT; // Initial direction
    rgb = new Rgb;
}

int8_t Enemy::checkBody(Lizard& body)
{ // to check that there is no collosion between the two bodys
    for (int i = 0; i < length; i++)
        for (int x = 0; x < length; ++x)
            if (body.getBody()[x].x == arr[i].x && body.getBody()[x].y == arr[i].y)
                return false;
    return true;
}

void Enemy::draw() const
{
    for (int i = 0; i < length; i++)
    {
        setcolor(BLACK);
        rectangle(arr[i].x, arr[i].y, arr[i].x + 30, arr[i].y + 30);
        if (i == 0)
            setfillstyle(SOLID_FILL, COLOR(rgb->EH[0], rgb->EH[1], rgb->EH[2])); // Head has a darker color than the body
        else
            setfillstyle(SOLID_FILL, COLOR(rgb->EB[0], rgb->EB[1], rgb->EB[2]));
        floodfill(arr[i].x + 15, arr[i].y + 15, BLACK);
    }
}

void Enemy::append(Lizard& body)
{
    // Adds 1 to length if player ate 3
    if (!(body.getLength() % 3)) 
        length++;
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