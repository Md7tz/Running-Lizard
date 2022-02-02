#include "GameManager/gameManager.h"
using namespace GAME;

#pragma region Fields
Menu* GameManager::menu;
Grid* GameManager::grid;

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
#pragma endregion

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
    delayAmt        = 60;							
    lifeCount       = 3; 							
    skipFrame       = true;							
    isPlaying       = true;	
    revealEnemy     = false; 						
    collide         = false;							
    restart         = false;							
    score[4]        = '0';
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
            if(SFX) PlaySound("Assets/SFX/eat sound.wav", NULL, SND_ASYNC);
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
    setcolor(WHITE);
    setbkcolor(COLOR(18,39,34)); 
    settextjustify(0, 2);
    settextstyle(font_names::SANS_SERIF_FONT, HORIZ_DIR, 1);

    // Calculate score from body length
    bodyLength = player.getLength();
    strncpy(score, std::to_string((bodyLength - 2) * 10).c_str(), 4);
    outtextxy(398, 0, score);

    // Regenerate new poison position
    // Check if player ate 3 poison
    if (poison.update(player.getPosx(), player.getPosy()))
    {
        if(SFX) PlaySound("Assets/SFX/poison eat.wav", NULL, SND_ASYNC);
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

    readimagefile("Assets/Sprites/border.gif", 0, 535, 816, 598);

    if (atoi(score) < 100) 
        readimagefile("Assets/Sprites/normal.gif", 120, 550, 190, 595);
    if (atoi(score) >= 100 && atoi(score) < 200)
    {
        readimagefile("Assets/Sprites/fast.gif", 120, 550, 190, 595);
        delayAmt = 40;
    }
    if (atoi(score) >= 200)
    {
        readimagefile("Assets/Sprites/insane.gif", 120, 550, 190, 595);
        delayAmt = 25;
        revealEnemy = true; 
    }
    // Check if player reached max length -> Won
    if (player.getLength() == 32)
    {
        readimagefile("Assets/Sprites/victory.gif", 355, 250, 455, 350);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
        outtextxy(155, 200, (char*)"You Won! Press R to Restart");
        isPlaying = false;
    }
    // Retry prompt
    if (!isPlaying && player.getLength() != 32)
    {
        readimagefile("Assets/Sprites/gameOver.gif", 310, 250, 500, 350);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
        outtextxy(250, 200, (char*)" Press R to Retry ");
    }

    // Draw Controls 
    readimagefile("Assets/Sprites/Arrows.gif", 640, 550, 710, 595);
    readimagefile("Assets/Sprites/WASD.gif", 730, 550, 800, 595);
    readimagefile("Assets/Sprites/speed.gif", 5, 555, 105, 590);

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

        // Reset page
        delete grid;
        page = 1 - page;
    }
}