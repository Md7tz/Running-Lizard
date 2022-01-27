/*  Utility Functions
        inline void setup(int8_t&);
        inline void generationHandler(Edible&, Edible&, Poison&, Player&);
        inline void inputHandler(Player&, Enemy&, bool&, bool&, bool&);
        void collisionHandler(Player&, Enemy&, bool&, bool&, bool&, bool&, Lives&);
        void uiHandler(Player&, Poison&, Edible[2], uint8_t&, char[4], char[10], Lives&, uint8_t&, int16_t&, bool&, bool&);
        void gameObjectsHandler(Player&, Enemy&, Poison&, Edible[], bool&, bool&, int8_t);
*/

#pragma region Functions

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

void collisionHandler(Player& player, Enemy& enemy, bool& collide, bool& skip, bool& reveal, bool& gameState, Lives& lives) {
    if (reveal)
    {
        if (!skip)
            enemy.update();
        skip = !skip;

        // change the direciton randomly
        enemy.changeDir(0);

        // Decrease a life if there is any collsion between the body and enemy
        if (!enemy.checkBody(player) && collide == false)
        {
            lives-=1;
            collide = true;
            if (lives == 0)
                gameState = false;
        }
        if (enemy.checkBody(player)) {
            collide = false;
        }
    }
}

void uiHandler(Player& player, Poison& poison, Edible fruit[2], uint8_t& bodyLength, char score[4], char speed[10], Lives& lives, uint8_t& padding, int16_t& delay, bool& reveal, bool& gameState) {
    setbkcolor(COLOR(18,39,34)); //18 39 34
    settextjustify(0, 2);
    // Score
    settextstyle(font_names::SANS_SERIF_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    readimagefile("Assets/Sprites/Border1.gif", 0, 535, 816, 598);

    // Calculate score from body length
    bodyLength = player.getLength();
    strncpy(score, std::to_string((bodyLength - 2) * 10).c_str(), 4);

    // Display score
    // outtextxy(20, 545, (char*)"SCORE");
    outtextxy(398, 0, score);

    // Game State
    // Regenerate new poison position
    // Check if player ate 3 poison
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    if (poison.update(player.getPosx(), player.getPosy()))
    {
        poison.generate(player.getPosx(), player.getPosy());
        generationHandler(fruit[0], fruit[1], poison, player);
        lives-=1;
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
        outtextxy(170, 545, (char*)"PLAYING");
    }

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
    // setcolor(BLACK);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(20, 575, (char*)"Speed");
    outtextxy(90, 575, speed);

    // Draw Exit Key
    // setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(20, 545, (char*)" PRESS 'ESC' to EXIT ");

    // Check if player reached max length -> Won
    if (player.getLength() == 32)
    {
        // setcolor(BLACK);
        outtextxy(160, 545, (char*)"Victory!");
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
        outtextxy(155, 200, (char*)"You Won! Press R to Restart");
        gameState = false;
    }
    // Retry prompt
    if (!gameState && player.getLength() != 32)
    {
        // setcolor(BLACK);
        outtextxy(160, 545, (char*)"GAME OVER");
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
        outtextxy(250, 200, (char*)" Press R to Retry ");
    }

    // Draw Controls - WASD
    readimagefile("Assets/Sprites/WASD.gif", 720, 540, 810, 595);

    // Draw Controls - Arrow Keys
    readimagefile("Assets/Sprites/Arrows.gif", 620, 540, 710, 593);


    // Draw lives
    lives.draw();
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
        fruit[i].draw("Assets/Sprites/apple.gif");

    // Draw poison
    poison.draw("Assets/Sprites/poison.gif");

    player.draw();
    if (reveal)
        enemy.draw();

}
#pragma endregion Functions
