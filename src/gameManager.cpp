#include "GameManager/gameManager.h"

Menu* GameManager:: menu;
Grid* GameManager:: grid;

Lives GameManager::lives;
Player GameManager::player;
Enemy GameManager::enemy;
Edible GameManager::fruit[2]; 	    
Poison GameManager::poison;

uint8_t GameManager::bodyLength; 							    
int8_t GameManager::page;   		 						    
int8_t GameManager::fruitCount;
int16_t GameManager::lifeCount; 							    
int16_t GameManager::delayAmt;							    

bool GameManager::skipFrame;							        
bool GameManager::isPlaying;							        
bool GameManager::revealEnemy; 						        
bool GameManager::collide;							        
bool GameManager::restart;							        

char GameManager::score[4];
char GameManager::speed[10];

void GameManager::setup() {
    setactivepage(page);
    setvisualpage(1 - page);
    cleardevice();
}

void GameManager::setAll() {
    fruitCount      = Edible::getCount();
    lives           = Lives();
    player          = Player(&lives);
    enemy           = Enemy(300, 300);
    fruit[0]        = Edible(1);
    fruit[1]        = Edible(5); 	
    poison          = Poison();
    page            = 1;   		 																		
    delayAmt        = 90;							
    lifeCount       = 3; 							
    skipFrame       = true;							
    isPlaying       = true;							
    revealEnemy     = false; 						
    collide         = false;							
    restart         = false;							
    score[4]        = '0';
    strcpy(speed, "Normal");
}

void GameManager::generationHandler()
{
    if ((fruit[0].foodPos.x == poison.foodPos.x && fruit[0].foodPos.y == poison.foodPos.y) ||
        (fruit[1].foodPos.x == poison.foodPos.x && fruit[1].foodPos.y == poison.foodPos.y))
    {
        poison.generate(player.getPosx(), player.getPosy());
    }
}

void GameManager::inputHandler() {
    if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
        player.changeDir(LEFT);
    if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
        player.changeDir(UP);
    if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
        player.changeDir(RIGHT);
    if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
        player.changeDir(DOWN);
    if (GetAsyncKeyState(VK_ESCAPE))
        exit(1); 
    if (GetAsyncKeyState('R'))
        restart = true;
    if (isPlaying == true && !player.update())
        isPlaying = false;
}

void GameManager::collisionHandler() {
    if (revealEnemy)
    {
        if (!skipFrame)
            enemy.update();
        skipFrame = !skipFrame;

        // change the direciton randomly
        enemy.changeDir();

        // Decrease a life if there is any collsion between the body and enemy
        if (!enemy.checkBody(player) && collide == false)
        {
            lives-=1;
            collide = true;
            if (lives == 0)
                isPlaying = false;
        }
        if (enemy.checkBody(player)) {
            collide = false;
        }
    }
}

void GameManager::gameObjectsHandler() {
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
    if (revealEnemy)
        enemy.draw();

}

void GameManager::uiHandler() {
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
        generationHandler();
        lives-=1;
        if (poison.getHit() == 3)
        {
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
            outtextxy(160, 545, (char*)"GAME OVER");
            isPlaying = false;
        }
    }

    if (isPlaying)
    {
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        outtextxy(170, 545, (char*)"PLAYING");
    }

    // Progressive speed
    if (atoi(score) >= 100)
    {
        delayAmt = 40;
        strcpy(speed, "Fast");
    }
    if (atoi(score) >= 200)
    {
        delayAmt = 25;
        strcpy(speed, "Insane");
        revealEnemy = true; // now enemy will be revealed
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
        isPlaying = false;
    }
    // Retry prompt
    if (!isPlaying && player.getLength() != 32)
    {
        // setcolor(BLACK);
        outtextxy(160, 545, (char*)"GAME OVER");
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
        outtextxy(250, 200, (char*)" Press R to Retry ");
    }

    // Draw Controls 
    readimagefile("Assets/Sprites/Arrows.gif", 640, 550, 710, 595);
    readimagefile("Assets/Sprites/WASD.gif", 730, 550, 800, 595);

    // Draw lives
    lives.draw();
}

void GameManager::initGame() {
    G_MENU:
    menu = new Menu();
    while (!(menu->getGameState())) {
        #if DEBUG
            Timer timer;
        #endif
        menu->pagesHandler();
        menu->menuInputHandler();
        delay(100);
    }
    delete menu;

    // Start Block
    G_START:
    setAll();

    // Generate new pos for food
    for (uint8_t i = 0; i < fruitCount; i++)
        fruit[i].generate(player.getPosx(), player.getPosy());

    // Generate new pos for poison
    poison.generate(player.getPosx(), player.getPosy());
    generationHandler();

    while (true)
    {
        #if DEBUG == true
            Timer timer;
        #endif
        setup();

        // Create a grid in dynamic memory
        grid = new Grid();
        grid->draw();

        inputHandler();
        collisionHandler();
        gameObjectsHandler();
        uiHandler();

        // Checks game state
        if (restart) {
            cleardevice();
            goto G_START;
        };

        // Control speed between frames
        delay(delayAmt);

        // Free grid from memory
        delete grid;

        // Reset page
        page = 1 - page;
    }
}