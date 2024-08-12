// Gameplay.h

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "DestructibleBlock.h"
#include "IndestructibleBlock.h"
#include "Enemy.h"
#include "Boba.h"
//#include "Bomb.h"

using namespace sf;

class Gameplay
{
public:
    Gameplay(bool& isgo,const Texture& gameovertexture,const Texture& bgTexture, const Texture& blockTexture, const Texture& bobaTexture, const Texture& hay, const Texture& bombTexture, const Texture& enemyTexture, const Texture& door, float margin, float drawableWidth, float drawableHeight, int numbombs, int numEnemies, bool& llevelCompleted, Text& timertext, int s);

    ~Gameplay();

    void draw(RenderWindow& window);
    void update(RenderWindow& window);
    void moveBoba(float dx, float dy);
    bool isGameOver() ;
private:
    FloatRect mazeBounds;
   // Block* createBlock(bool isDestructible, float blockSizeWidth, float blockSizeHeight, int row, int col);
   // void checkGameOverConditions();
    Texture gameovertexture;
    Sprite stext;
    int score;
    Text scoret;
    Clock clock;
    float elapsedTime; // To store the elapsed time
    Text timerText;
    void initializeBoba();
    void initializeEnemies();
    void setupExitDoor();
    void checkExitDoorVisibility();
    void revealExitDoor();
    bool shouldRevealExitDoor(int index);
    void removeBlock(int index);
    void handleBombExplosion(Bomb* bomb, RenderWindow& window);
    bool isBobaInExplosionRange(sf::FloatRect explosionBounds) const;
    void moveEnemyRandomly(Enemy* enemy);
    bool checkCollisionWithEnemies();
    void checkBobaExitDoorCollision();
    bool doesBlockExistAt(float x, float y, float tolerance);
    void createMaze2(float blockSizeWidth, float blockSizeHeight);
    void createMaze3(float blockSizeWidth, float blockSizeHeight);
    //put in level
    void createMaze(float blockSizeWidth, float blockSizeHeight);



    Font font;
    Text blocksLeftText;
    Texture blockTexture;
    Texture bobaTexture;
    Texture hay;
    Texture bombTexture;
    Texture enemytexture;
    Texture door;
    bool levelCompleted;
    float margin;
    float drawableWidth;
    float drawableHeight;
    int numbombs;
    int numenemies;
    bool gameOver;
    float explosionRange;

    Block** blocks;
    int numBlocks;
    int numRows;
    int numCols;

    Enemy** enemies;
    Boba* boba;
    Sprite exitDoor;
    bool exitDoorVisible;
};

#endif // GAMEPLAY_H
