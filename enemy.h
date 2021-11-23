
class Enemy : public Lizard
{

public:
    Enemy(int16_t x, int16_t y);
    uint8_t update();
    int8_t checkBody(Lizard &body);
    void draw() const;
    void append(Lizard &);
    void changeDirTo();
};

Enemy ::Enemy(int16_t x, int16_t y)
{
    arr[0].x = x;      // Initial x value for head
    arr[0].y = y;      // Initial y value for head
    length = 2;        // Initial length
    direction = RIGHT; // Initial direction
    offset = 30;
    rgb = new Rgb;
}

int8_t Enemy::checkBody(Lizard &body)
{ // to check that there is no collosion between the two bodys
    for (int i = 0; i < length; i++)
        for (int x = 0; x < length; ++x)
            if (body.getBody()[x].x == arr[i].x && body.getBody()[x].y == arr[i].y)
                return 0;
    return 1;
}

void Enemy::draw() const
{ // Draws the lizard
    // Colors
    // 179, 170, 0
    // 245, 232, 0
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

uint8_t Enemy::update()
{
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

void Enemy::append(Lizard &body)
{
    if (length < 33 && !(body.getLength() % 2)) // Prevents length from exceeding 32
        length++;
}

void Enemy::changeDirTo()
{
    // generate a random number in range from 0-3 direction for the enemy lizard
    srand(time(NULL));
    direction = (rand() % 3) + 1;
}