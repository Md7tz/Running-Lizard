/* 1- Drawing Screen UI
        void drawKeys(int16_t, int16_t);
        void drawLives(const int16_t, uint8_t&);
        void drawInstruction(int16_t, int16_t, int16_t, int16_t);
*/

/* 2- Utility Functions
        inline void setup(int8_t&);
        inline void generationHandler(Edible&, Edible&, Poison&, Player&);
        inline void inputHandler(Player&, Enemy&, bool&, bool&, bool&);
        void collisionHandler(Player&, Enemy&, bool&, bool&, bool&, bool&, int16_t&);
        void uiHandler(Player&, Poison&, Edible[2], uint8_t&, char[4], char[10], int16_t&, uint8_t&, int16_t&, bool&, bool&);
        void gameObjectsHandler(Player&, Enemy&, Poison&, Edible[], bool&, bool&, int8_t);
*/

#pragma region Functions
/******************** Screen UI ********************/

// Draw key boxes
void drawKeys(int16_t x, int16_t y)
{
    for (int16_t i = 0; i < 4; i++)
    {
        rectangle(x, y, x + 22, y + 20);
        if (i == 0)
        {
            y += 25;
            x -= 50;
        }
        x += 25;
    }
}

// Draw lives left
void drawLives(const int16_t counter, uint8_t& padding)
{
    uint8_t temp = padding;
    setcolor(RED);
    for (int16_t j = 0; j < 3; j++)
    {
        arc(485 + padding, 555, 0, 180, 10);
        arc(465 + padding, 555, 0, 180, 10);
        arc(475 + padding, 555, 180, 360, 20);
        padding += 50;
    }
    padding = temp;
    for (int16_t i = 0; i < counter; i++)
    {
        setfillstyle(SOLID_FILL, RED);
        floodfill(475 + padding, 565, RED);
        padding += 50;
    }
    padding = 0;
}

// Draw instructions
void drawInstruction(int16_t x, int16_t y, int16_t size, int16_t offset)
{
    // Text
    setcolor(COLOR(255, 45, 0));
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(630, 575, (char*)"FOOD");
    // Food
    setcolor(RED);
    rectangle(x, y, x + size, y + size);
    setfillstyle(INTERLEAVE_FILL, RED);
    floodfill(x + (size / 2), y + (size / 2), RED);
    // Text
    setcolor(COLOR(10, 255, 0));
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(705, 575, (char*)"POISON");
    // Poison
    setcolor(GREEN);
    rectangle(x + offset, y, x + size + offset, y + size);
    setfillstyle(INTERLEAVE_FILL, GREEN);
    floodfill(x + (size / 2) + offset, y + (size / 2), GREEN);
}


/******************** Utility Functions ********************/

inline void setup(int8_t& page) {
    setactivepage(page);
    setvisualpage(1 - page);
    cleardevice();
}

// Generates new position if the position is equal to the food pos
inline void generationHandler(Edible& f1, Edible& f2, Poison& p, Player& b)
{
    if ((f1.foodPos.x == p.foodPos.x && f1.foodPos.y == p.foodPos.y) ||
        (f2.foodPos.x == p.foodPos.x && f2.foodPos.y == p.foodPos.y))
    {
        p.generate(b.getPosx(), b.getPosy());
    }
}

inline void inputHandler(Player& player, bool& restart, bool& gameState) {
    // Input Handler
    if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
        player.changeDir(LEFT);
    if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
        player.changeDir(UP);
    if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
        player.changeDir(RIGHT);
    if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
        player.changeDir(DOWN);
    if (GetAsyncKeyState(VK_ESCAPE))
        exit(1); // Exit from game
    if (GetAsyncKeyState('R'))
        restart = true;
    if (gameState == true && !player.update())
        gameState = false;
}

void collisionHandler(Player& player, Enemy& enemy, bool& collide, bool& skip, bool& reveal, bool& gameState, int16_t& lives) {
    if (reveal)
    {
        if (!skip)
            enemy.update();
        skip = !skip;

        // change the direciton randomly
        enemy.changeDir();

        // Decrease a life if there is any collsion between the body and enemy
        if (!enemy.checkBody(player) && collide == false)
        {
            lives -= 1;
            collide = true;
            if (lives == 0)
                gameState = false;
        }
        if (enemy.checkBody(player)) {
            collide = false;
        }
    }
}

void uiHandler(Player& player, Poison& poison, Edible fruit[2], uint8_t& bodyLength, char score[4], char speed[10], int16_t& lives, uint8_t& padding, int16_t& delay, bool& reveal, bool& gameState) {
    settextjustify(0, 2);
    // Score
    settextstyle(font_names::SANS_SERIF_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);

    // Calculate score from body length
    bodyLength = player.getLength();
    strncpy(score, std::to_string((bodyLength - 2) * 10).c_str(), 4);

    // Display score
    outtextxy(20, 545, (char*)"SCORE");
    outtextxy(90, 545, score);

    // Game State
    // Regenerate new poison position
    // Check if player ate 3 poison
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    if (poison.update(player.getPosx(), player.getPosy()))
    {
        poison.generate(player.getPosx(), player.getPosy());
        generationHandler(fruit[0], fruit[1], poison, player);
        lives--;
        if (poison.getHit() == 3)
        {
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
            outtextxy(160, 545, (char*)"GAME OVER");
            gameState = false;
        }
    }
    if (gameState)
    {
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        outtextxy(160, 545, (char*)"PLAYING");
    }

    // Draw Controls - WASD
    setcolor(WHITE);
    drawKeys(295, 545);

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(295, 545, (char*)" W ");
    outtextxy(270, 568, (char*)" A  ");
    outtextxy(295, 568, (char*)" S  ");
    outtextxy(320, 568, (char*)" D  ");

    // Draw Controls - Arrow Keys
    setcolor(BLACK);
    drawKeys(385, 545);
    // up arrow key
    line(388, 559, 395, 549);
    line(395, 549, 402, 559);
    // down arrow key
    line(388, 574, 395, 584);
    line(395, 584, 402, 574);
    // right arrow key
    line(415, 574, 428, 579);
    line(428, 579, 416, 584);
    // left arrow key
    line(378, 574, 365, 579);
    line(365, 579, 378, 584);

    // Progressive speed
    if (atoi(score) >= 100)
    {
        delay = 40;
        strcpy(speed, "Fast");
    }
    if (atoi(score) >= 200)
    {
        delay = 25;
        strcpy(speed, "Insane");
        reveal = true; // now enemy will be revealed
    }

    // Draw Speed
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(20, 575, (char*)"Speed");
    outtextxy(90, 575, speed);

    // Draw lives
    drawLives(lives, padding);

    // Draw Exit Key
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(630, 545, (char*)" PRESS 'ESC' to EXIT ");

    // Check if player reached max length -> Won
    if (player.getLength() == 32)
    {
        setcolor(WHITE);
        outtextxy(160, 545, (char*)"Victory!");
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
        outtextxy(155, 200, (char*)"You Won! Press R to Restart");
        gameState = false;
    }
    // Retry prompt
    if (!gameState && player.getLength() != 32)
    {
        setcolor(WHITE);
        outtextxy(160, 545, (char*)"GAME OVER");
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
        outtextxy(250, 200, (char*)" Press R to Retry ");
    }

    // Draw instruction
    drawInstruction(680, 575, 20, 90);
}

void gameObjectsHandler(Player& player, Enemy& enemy, Poison& poison, Edible fruit[2], bool& gameState, bool& reveal, int8_t fruitCount) {
    for (uint8_t i = 0; i < fruitCount; i++)
    {
        if (fruit[i].update(player.getPosx(), player.getPosy()))
        {
            fruit[i].generate(player.getPosx(), player.getPosy());
            player.append();
        }
    }

    // Draw food
    for (uint8_t i = 0; i < fruitCount; i++)
        fruit[i].draw();

    // Draw poison
    poison.draw();

    player.draw();
    if (reveal)
        enemy.draw();

}
#pragma endregion Functions
