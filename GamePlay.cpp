#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Gameplay.h"
//#include "Boba.h"
#include "Block.h"
#include "IndestructibleBlock.h"
#include "DestructibleBlock.h"
#include "Enemy.h"
#include <sstream>//for text
#include<ctime>
using namespace std;
using namespace sf;


Gameplay::Gameplay(bool& isgo, const Texture& gameovertexture,const Texture& bgTexture, const Texture& blockTexture, const Texture& bobaTexture, const Texture& hay, const Texture& bombTexture, const Texture& enemyTexture, const Texture& door, float margin, float drawableWidth, float drawableHeight, int numbombs, int numEnemies,bool& llevelCompleted, Text& timertext,int s)
    : gameOver(isgo),gameovertexture(gameovertexture), blockTexture(blockTexture), bobaTexture(bobaTexture), hay(hay), bombTexture(bombTexture), enemytexture(enemyTexture), margin(margin), drawableWidth(drawableWidth), drawableHeight(drawableHeight), numbombs(numbombs), numenemies(numEnemies), explosionRange(150.0f), door(door),score(s) // Initialize the explosion range here
{
    //score = 0;
    //scoret.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\ARIALBD 1.TTF"
    if (!font.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\ARIALBD 1.TTF"))
    {
        cout << "nahi hoa load";
        
    }
    
    scoret.setFont(font);
    scoret.setCharacterSize(50);
    scoret.setPosition(700, 30);
    blocksLeftText.setFont(font);
    blocksLeftText.setCharacterSize(50);
    //blocksLeftText.setFillColor(Color::White);
    blocksLeftText.setPosition( 20, 30); // Position the text on the right side of the screen



    clock.restart(); // Start the clock
    timerText = timertext;
    levelCompleted = levelCompleted;
    //exitDoor.setTexture(door);
    srand(static_cast<unsigned int>(time(nullptr)));
    exitDoor.setTexture(door);
    exitDoor.setScale(1.5f, 1.5f);//EXIT DOOR SIZE
    exitDoorVisible = false;
    float blockSize = (min(drawableWidth / 16.0f, drawableHeight / 12.0f)) * 1.5f; // Increase size by a factor of 1.5

    numRows = 12;
    numCols = 15;
    numBlocks = 120;

   // blocks = new Block * [numBlocks]; // Using raw pointers, consider switching to smart pointers in the future
    blocks = new Block * [numBlocks];
    for (int i = 0; i < numBlocks; ++i) {
        blocks[i] = nullptr;
    }
    //blocks = nullptr;
    createMaze(blockSize, blockSize);
    initializeBoba();
    enemies = new Enemy * [numEnemies]; // Using raw pointers, consider switching to smart pointers in the future
    initializeEnemies();//being called in different mazes
}
//void Gameplay::initializeEnemies()
//{
//    float enemySize = 120.0f; // Size for each enemy
//    float minimumDistance = 150.0f; // Minimum distance between enemies to avoid clustering
//
//    for (int i = 0; i < numenemies; ++i)
//    {
//        bool positionFound = false;
//        float x, y;
//
//        while (!positionFound)
//        {
//            x = margin + rand() % static_cast<int>(drawableWidth - enemySize);
//            y = margin + rand() % static_cast<int>(drawableHeight - enemySize);
//            FloatRect enemyBounds(x, y, enemySize, enemySize);
//
//            bool collisionDetected = false;
//
//            // Check collision with blocks
//            for (int j = 0; j < numBlocks; ++j) {
//                if (blocks[j] != nullptr) {
//                    FloatRect blockBounds = blocks[j]->getSprite().getGlobalBounds();
//                    if (blockBounds.intersects(enemyBounds)) {
//                        collisionDetected = true;
//                        break;
//                    }
//                }
//            }
//
//            // Check collision with already placed enemies and ensure minimum distance
//            for (int k = 0; k < i; ++k) {
//                if (enemies[k] != nullptr) {
//                    FloatRect otherEnemyBounds = enemies[k]->getBounds();
//                    float otherX = otherEnemyBounds.left + otherEnemyBounds.width / 2;
//                    float otherY = otherEnemyBounds.top + otherEnemyBounds.height / 2;
//                    float distance = sqrt(pow(x + enemySize / 2 - otherX, 2) + pow(y + enemySize / 2 - otherY, 2));
//
//                    // Check both overlap and minimum distance
//                    if (distance < minimumDistance || enemyBounds.intersects(otherEnemyBounds)) {
//                        collisionDetected = true;
//                        break;
//                    }
//                }
//            }
//
//            // Check if the enemy is too close to the bottom limit
//            if (y + enemySize > margin + drawableHeight - 50) // Adjust the bottom limit to ensure space for movement
//            {
//                collisionDetected = true;
//            }
//
//            // Check if the enemy is too close to Boba
//            if (boba != nullptr) {
//                FloatRect bobaBounds = boba->getBounds();
//                if (bobaBounds.intersects(enemyBounds)) {
//                    collisionDetected = true;
//                }
//            }
//
//            if (!collisionDetected) {
//                positionFound = true;
//            }
//        }
//
//        enemies[i] = new Enemy(enemytexture, enemySize, x, y);
//    }
//}
    void Gameplay::initializeEnemies()
    {
        // Seed the random number generator
        srand(static_cast<unsigned>(time(nullptr)));

        float enemySize = 120.0f; // Size for each enemy
        float minimumDistance = 150.0f; // Minimum distance between enemies to avoid clustering

        for (int i = 0; i < numenemies; ++i)
        {
            bool positionFound = false;
            float x, y;

            while (!positionFound)
            {
                x = margin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (drawableWidth - enemySize)));
                y = margin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (drawableHeight - enemySize)));
                FloatRect enemyBounds(x, y, enemySize, enemySize);

                bool collisionDetected = false;

                // Check collision with blocks
                for (int j = 0; j < numBlocks; ++j) {
                    if (blocks[j] != nullptr) {
                        FloatRect blockBounds = blocks[j]->getSprite().getGlobalBounds();
                        if (blockBounds.intersects(enemyBounds)) {
                            collisionDetected = true;
                            break;
                        }
                    }
                }

                // Check collision with already placed enemies and ensure minimum distance
                for (int k = 0; k < i; ++k) {
                    if (enemies[k] != nullptr) {
                        FloatRect otherEnemyBounds = enemies[k]->getBounds();
                        float otherX = otherEnemyBounds.left + otherEnemyBounds.width / 2;
                        float otherY = otherEnemyBounds.top + otherEnemyBounds.height / 2;
                        float distance = sqrt(pow(x + enemySize / 2 - otherX, 2) + pow(y + enemySize / 2 - otherY, 2));

                        // Check both overlap and minimum distance
                        if (distance < minimumDistance || enemyBounds.intersects(otherEnemyBounds)) {
                            collisionDetected = true;
                            break;
                        }
                    }
                }

                // Check if the enemy is too close to the bottom limit
                if (y + enemySize > margin + drawableHeight - 50) // Adjust the bottom limit to ensure space for movement
                {
                    collisionDetected = true;
                }

                // Check if the enemy is too close to Boba
                if (boba != nullptr) {
                    FloatRect bobaBounds = boba->getBounds();
                    if (bobaBounds.intersects(enemyBounds)) {
                        collisionDetected = true;
                    }
                }

                if (!collisionDetected) {
                    positionFound = true;
                }
            }

            enemies[i] = new Enemy(enemytexture, enemySize, x, y);
        }
    }

    //void Gameplay::initializeBoba()
    //{
    //    // Seed the random number generator
    //    srand(static_cast<unsigned>(time(nullptr)));

    //    float bobaSize = 100.0f; // Size for the Boba object
    //    boba = new Boba(bobaTexture, bobaSize, bombTexture, numbombs);

    //    bool positionFound = false;
    //    float x, y;

    //    while (!positionFound)
    //    {
    //        // Generate random positions
    //        x = margin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (drawableWidth - bobaSize)));
    //        y = margin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (drawableHeight - bobaSize)));
    //        FloatRect bobaBounds(x, y, bobaSize, bobaSize);

    //        bool collisionDetected = false;

    //        // Check for collision with blocks
    //        for (int i = 0; i < numBlocks; ++i)
    //        {
    //            if (blocks[i] != nullptr)
    //            {
    //                FloatRect blockBounds = blocks[i]->getSprite().getGlobalBounds();
    //                if (blockBounds.intersects(bobaBounds))
    //                {
    //                    collisionDetected = true;
    //                    break;
    //                }
    //            }
    //        }

    //        // Check for collision with enemies
    //        if (!collisionDetected)
    //        {
    //            for (int i = 0; i < numenemies; ++i)
    //            {
    //                if (enemies[i] != nullptr)
    //                {
    //                    FloatRect enemyBounds = enemies[i]->getBounds();
    //                    if (enemyBounds.intersects(bobaBounds))
    //                    {
    //                        collisionDetected = true;
    //                        break;
    //                    }
    //                }
    //            }
    //        }

    //        if (!collisionDetected)
    //        {
    //            positionFound = true;
    //        }
    //    }

    //    if (positionFound)
    //    {
    //        boba->setPosition(x, y);
    //        // std::cout << "Boba initialized at position (" << x << ", " << y << ")" << std::endl;
    //    }
    //    else
    //    {
    //        // std::cout << "No suitable position found for Boba initialization!" << std::endl;
    //    }
    //}
bool Gameplay::isBobaInExplosionRange(sf::FloatRect explosionBounds) const {
    if (boba != nullptr) {
        sf::FloatRect bobaBounds = boba->getBounds();
        return explosionBounds.intersects(bobaBounds);
    }
    return false;
}
Gameplay::~Gameplay()
{
    //for (int i = 0; i < numBlocks; ++i)
    //{
    //    removeBlock(i);  // Clean up blocks
    //}

    // Clean up blocks
    for (int i = 0; i < numBlocks; ++i)
    {
        delete blocks[i];
    }
    delete[] blocks;
    blocks = nullptr;
    // Clean up Boba
    delete boba;
    boba = nullptr;
    // Clean up enemies
    for (int i = 0; i < numenemies; ++i)
    {
        delete enemies[i];
    }
    delete[] enemies;
    enemies = nullptr;
}
void Gameplay::initializeBoba()
{
    float bobaSize = 100.0f; // Size for the boba object
    boba = new Boba(bobaTexture, bobaSize, bombTexture, numbombs);

    bool positionFound = false;
    float x = margin + 200;
    float y = margin + 200;
    float increment = bobaSize / 2; // Smaller increment to check more positions

    while (!positionFound && y <= margin + drawableHeight - bobaSize)
    {
        bool collisionDetected = false;
        FloatRect bobaBounds(x, y, bobaSize, bobaSize);

        // Check for collision with blocks
        for (int i = 0; i < numBlocks; ++i)
        {
            if (blocks[i] != nullptr)
            {
                FloatRect blockBounds = blocks[i]->getSprite().getGlobalBounds();
                if (blockBounds.intersects(bobaBounds))
                {
                    collisionDetected = true;
                    break;
                }
            }
        }

        //// Check for collision with enemies
        //if (!collisionDetected)
        //{
        //    for (int i = 0; i < numenemies; ++i)
        //    {
        //        if (enemies[i] != nullptr)
        //        {
        //            FloatRect enemyBounds = enemies[i]->getsprite().getGlobalBounds();
        //            if (enemyBounds.intersects(bobaBounds))
        //            {
        //                collisionDetected = true;
        //                break;
        //            }
        //        }
        //    }
        //}

        if (!collisionDetected)
        {
            positionFound = true;
        }
        else
        {
            x += increment;
            if (x > margin + drawableWidth - bobaSize)
            {
                x = margin + 20;
                y += increment;
            }
        }
    }

    if (positionFound)
    {
        boba->setPosition(x, y);
        // std::cout << "Boba initialized at position (" << x << ", " << y << ")" << std::endl;
    }
    else
    {
        // std::cout << "No suitable position found for Boba initialization!" << std::endl;
    }
}
void Gameplay::createMaze3(float blockSizeWidth, float blockSizeHeight)
{
    float vertSizeFit = 88.0f;
    float horizSizeFit = 64.0f;
    int index = 0;
    mazeBounds = FloatRect(margin, margin, 0, 0); // Initialize with dummy values

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(0)));

    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            if (index < numBlocks)
            {
                if (blocks != nullptr)
                {
                    // Randomly determine if the block should be destructible or indestructible
                    bool isDestructible = ((row + col) % 3 == 0); // New pattern: Every third block

                    // Allocate the block with the selected type
                    if (isDestructible)
                    {
                        blocks[index] = new DestructibleBlock(blockTexture, 67); // Use destructible block
                    }
                    else
                    {
                        blocks[index] = new IndestructibleBlock(hay, 67); // Use indestructible block
                    }

                    // Set the position of the block
                    if (row == 0 || col == 0 || (row % 3 == 0 && col % 3 == 0))
                    {
                        blocks[index]->setPosition(margin + col * blockSizeWidth - horizSizeFit, margin + row * blockSizeHeight - vertSizeFit);
                    }
                    float blockPosX = margin + col * blockSizeWidth - horizSizeFit;
                    float blockPosY = margin + row * blockSizeHeight - vertSizeFit;

                    float blockRight = blockPosX + blockSizeWidth;
                    float blockBottom = blockPosY + blockSizeHeight;

                    mazeBounds.left = std::min(mazeBounds.left, blockPosX);
                    mazeBounds.top = std::min(mazeBounds.top, blockPosY);
                    mazeBounds.width = std::max(mazeBounds.width, blockRight - mazeBounds.left);
                    mazeBounds.height = std::max(mazeBounds.height, blockBottom - mazeBounds.top);

                    ++index;
                }
            }
        }
    }

    setupExitDoor();
    initializeBoba();
    initializeEnemies();
}

void Gameplay::createMaze2(float blockSizeWidth, float blockSizeHeight)
{
    numenemies++;
    float vertSizeFit = 88.0f;
    float horizSizeFit = 64.0f;
    int index = 0;

    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            if (index < numBlocks)
            {
                if (blocks != nullptr)
                {


                    bool isDestructible = ((row + col) % 2 == 0) && (row != 0 && col == 0); // Alternating pattern condition
                    blocks[index] = new IndestructibleBlock(hay, 67);// min(blockSizeWidth, blockSizeHeight));
                    if (isDestructible)
                    {
                        blocks[index] = new IndestructibleBlock(hay, 67);// min(blockSizeWidth, blockSizeHeight));
                    }

                    else
                    {
                        blocks[index] = new DestructibleBlock(blockTexture, 67);// min(blockSizeWidth, blockSizeHeight));
                    }

                    if (row == 0 || col == 0 || (col % 2 == 0 && row % 2 == 0))
                    {
                        blocks[index]->setPosition(margin + col * blockSizeWidth - horizSizeFit, margin + row * blockSizeHeight - vertSizeFit);
                    }

                    ++index;
                }
            }
        }
    }

    setupExitDoor();
        initializeBoba();
        initializeEnemies();
    }

void Gameplay::createMaze(float blockSizeWidth, float blockSizeHeight)
{
    float vertSizeFit = 88.0f;
    float horizSizeFit = 64.0f;
    int index = 0;
    mazeBounds = FloatRect(margin, margin, 0, 0); // Initialize with dummy values

    // Seed the random number generator
    srand(static_cast<unsigned>(std::time(0)));
   
    
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            if (index < numBlocks)
            {
                if (blocks != nullptr)
                {
                    // Randomly determine if the block should be destructible or indestructible
                    bool isDestructible = std::rand() % 2 == 0; // 50% chance

                    // Allocate the block with random type
                    if (isDestructible)
                    {
                        blocks[index] = new DestructibleBlock(blockTexture, 67); // Use destructible block
                    }
                    else
                    {
                        blocks[index] = new IndestructibleBlock(hay, 67); // Use indestructible block
                    }
                    if (row == 0 || col == 0 || (col % 2 == 0 && row % 2 == 0))
                    {
                        blocks[index]->setPosition(margin + col * blockSizeWidth - horizSizeFit, margin + row * blockSizeHeight - vertSizeFit);
                    }
                    // Set the position of the block
                   
                    float blockPosX = margin + col * blockSizeWidth - horizSizeFit;
                    float blockPosY = margin + row * blockSizeHeight - vertSizeFit;

                    float blockRight = blockPosX + blockSizeWidth;
                    float blockBottom = blockPosY + blockSizeHeight;
                   // removeBlock(0);
                    mazeBounds.left = std::min(mazeBounds.left, blockPosX);
                    mazeBounds.top = std::min(mazeBounds.top, blockPosY);
                    mazeBounds.width = std::max(mazeBounds.width, blockRight - mazeBounds.left);
                    mazeBounds.height = std::max(mazeBounds.height, blockBottom - mazeBounds.top);

                    ++index;
                }
            }
        }
    }

    setupExitDoor();
}
//
//void Gameplay::createMaze(float blockSizeWidth, float blockSizeHeight)
//{
//    float vertSizeFit = 88.0f;
//    float horizSizeFit = 64.0f;
//    int index = 0;
//
//    for (int row = 0; row < numRows; ++row)
//    {
//        for (int col = 0; col < numCols; ++col)
//        {
//            if (index < numBlocks)
//            {
//                if (blocks != nullptr)
//                {
//
//
//                    bool isDestructible = ((row + col) % 2 == 0) && (row != 0 && col == 0); // Alternating pattern condition
//                    blocks[index] = new IndestructibleBlock(hay, 67);// min(blockSizeWidth, blockSizeHeight));
//                    if (isDestructible)
//                    {
//                        blocks[index] = new IndestructibleBlock(hay, 67);// min(blockSizeWidth, blockSizeHeight));
//                    }
//
//                    else
//                    {
//                        blocks[index] = new DestructibleBlock(blockTexture, 67);// min(blockSizeWidth, blockSizeHeight));
//                    }
//
//                    if (row == 0 || col == 0 || (col % 2 == 0 && row % 2 == 0))
//                    {
//                        blocks[index]->setPosition(margin + col * blockSizeWidth - horizSizeFit, margin + row * blockSizeHeight - vertSizeFit);
//                    }
//
//                    ++index;
//                }
//            }
//        }
//    }
//
//    setupExitDoor();
//}

//NOT ACTUAL JUST SO IK WHERE DOOR IS 
//void Gameplay::setupExitDoor()
//{
//    int doorRow = 5;
//    int doorCol = 0;
//    if (doorRow < numRows && doorCol < numCols && blocks != nullptr)
//    {
//        int doorIndex = doorRow * numCols + doorCol;
//        if (blocks[doorIndex] != nullptr && blocks[doorIndex]->isDestructible())
//        {
//            exitDoor.setTexture(door); // Set the texture for the sprite
//            exitDoor.setPosition(blocks[doorIndex]->getSprite().getPosition());
//
//            // Set the desired size by adjusting the scale
//            float desiredWidth = 50.f;
//            float desiredHeight = 50.f;
//            FloatRect bounds = exitDoor.getLocalBounds(); // Get the sprite's local bounds
//
//            // Calculate the scale factors
//            float scaleX = desiredWidth / bounds.width;
//            float scaleY = desiredHeight / bounds.height;
//            exitDoor.setScale(scaleX, scaleY); // Apply the scale
//
//            exitDoorVisible = false; // Initially hidden
//        }
//    }
//}
//ACTUAL RANDOM DOOR THING
void Gameplay::setupExitDoor()
{
    // Define a maximum number of destructible blocks
    const int maxDestructibleBlocks = 100; // Adjust if needed
    int destructibleBlockIndices[maxDestructibleBlocks];
    int count = 0;

    // Collect indices of all destructible blocks
    for (int i = 0; i < numBlocks; ++i)
    {
        if (blocks[i] != nullptr && blocks[i]->isDestructible())
        {
            if (count < maxDestructibleBlocks)
            {
                destructibleBlockIndices[count++] = i;
            }
        }
    }
   // removeBlock(0);
    // Check if we have any destructible blocks
    if (count > 0)
    {
        // Randomly select one of the destructible blocks
        int randomIndex = rand() % count;
        int doorIndex = destructibleBlockIndices[randomIndex];

        // Set the exit door texture and position
        exitDoor.setTexture(door); // Set the texture for the sprite
        exitDoor.setPosition(blocks[doorIndex]->getSprite().getPosition());

        // Set the desired size by adjusting the scale
        float desiredWidth = 50.f;
        float desiredHeight = 50.f;
        FloatRect bounds = exitDoor.getLocalBounds(); // Get the sprite's local bounds

        // Calculate the scale factors
        float scaleX = desiredWidth / bounds.width;
        float scaleY = desiredHeight / bounds.height;
        exitDoor.setScale(scaleX, scaleY); // Apply the scale

        exitDoorVisible = false; // Initially hidden
    }
    else
    {
        cout << "No destructible blocks available to place the exit door." << endl;
    }
}

void Gameplay::checkExitDoorVisibility()
{
    if (!exitDoorVisible)
    {
        for (int i = 0; i < numBlocks; ++i)
        {
            if (blocks[i] != nullptr && blocks[i]->isDestructible())
            {
                if (shouldRevealExitDoor(i))
                {
                    revealExitDoor();
                    break;
                }
            }
        }
    }
}

void Gameplay::revealExitDoor()
{
    exitDoorVisible = true;
    cout << "Exit door revealed!" << endl;
}
bool Gameplay::shouldRevealExitDoor(int index)
{
    if (blocks[index] == nullptr)
    {
        return false; // No block to check
    }

    // Get the bounds of the block
    FloatRect blockBounds = blocks[index]->getSprite().getGlobalBounds();

    // Get the bounds of the exit door
    FloatRect exitDoorBounds = exitDoor.getGlobalBounds();

    // Debug output to check bounds
    cout << "Block bounds: " << blockBounds.left << ", " << blockBounds.top << ", "
        << blockBounds.width << ", " << blockBounds.height << endl;
    cout << "Exit door bounds: " << exitDoorBounds.left << ", " << exitDoorBounds.top << ", "
        << exitDoorBounds.width << ", " << exitDoorBounds.height << endl;

    // Check if the exit door is covered by the block
    bool shouldReveal = exitDoorBounds.intersects(blockBounds);

    // Debug output for whether the exit door should be revealed
    cout << "Should reveal exit door: " << shouldReveal << endl;

    return shouldReveal;
}


bool Gameplay::doesBlockExistAt(float x, float y, float tolerance)
{
    for (int i = 0; i < numBlocks; ++i)
    {
        if (blocks[i] != nullptr)
        {
            FloatRect blockBounds = blocks[i]->getSprite().getGlobalBounds();
            FloatRect expandedBounds(blockBounds.left - tolerance, blockBounds.top - tolerance, blockBounds.width + 2 * tolerance, blockBounds.height + 2 * tolerance);

            if (expandedBounds.contains(x, y))
            {
                return true;
            }
        }
    }
    return false;
}
void Gameplay::moveBoba(float dx, float dy)
{
   // margin + col * blockSizeWidth - horizSizeFit, margin + row * blockSizeHeight - vertSizeFit
    if (boba != nullptr)
    {
        FloatRect originalBounds = boba->getBounds();
        boba->move(dx, dy);
        FloatRect newBounds = boba->getBounds();
        bool collisionDetected = false;

        for (int i = 0; i < numBlocks; ++i)
        {
            if (blocks[i] != nullptr)
            {
                FloatRect blockBounds = blocks[i]->getSprite().getGlobalBounds();
                if (blockBounds.intersects(newBounds))
                {
                    collisionDetected = true;
                    break;
                }
            }
        }

        if (collisionDetected)
        {
            boba->setPosition(originalBounds.left, originalBounds.top);
        }
        else
        {
            // Clamp the position to stay within maze boundaries
            float clampedX = std::max(mazeBounds.left, std::min(mazeBounds.left + mazeBounds.width - newBounds.width, newBounds.left));
            float clampedY = std::max(mazeBounds.top, std::min(mazeBounds.top + mazeBounds.height - newBounds.height, newBounds.top));
            boba->setPosition(clampedX, clampedY);
           /* float adjustedMarginX = margin -64+200;
            float adjustedMarginY = margin - 95;

            float newX = std::max(adjustedMarginX, std::min(adjustedMarginX + drawableWidth - newBounds.width, newBounds.left));
            float newY = std::max(adjustedMarginY, std::min(adjustedMarginY + drawableHeight - newBounds.height, newBounds.top));
            boba->setPosition(newX, newY);*/

        }
    }
   

}


//void Gameplay::moveBoba(float dx, float dy)
//{
//    float speed = 2;
//
//    // Seed the random number generator if it's not already done
//    static bool seeded = false;
//    //if (!seeded)
//    //{
//    //    //std::srand(static_cast<unsigned>(std::time(nullptr)));
//    //    seeded = true;
//    //}
//
//    if (boba != nullptr)
//    {
//        FloatRect originalBounds = boba->getBounds();
//       
//        float adjustedDx = dx * speed;
//        float adjustedDy = dy * speed;
//
//        boba->move(adjustedDx, adjustedDy);
//        FloatRect newBounds = boba->getBounds();
//        bool collisionDetected = false;
//
//        for (int i = 0; i < numBlocks; ++i)
//        {
//            if (blocks[i] != nullptr)
//            {
//                FloatRect blockBounds = blocks[i]->getSprite().getGlobalBounds();
//                if (blockBounds.intersects(newBounds))
//                {
//                    collisionDetected = true;
//                    break;
//                }
//            }
//        }
//
//        if (collisionDetected)
//        {
//            boba->setPosition(originalBounds.left, originalBounds.top);
//        }
//        else
//        {
//            float adjustedMarginX = margin - 64;
//            float adjustedMarginY = margin - 95;
//
//            float newX = max(adjustedMarginX, std::min(adjustedMarginX + drawableWidth - newBounds.width, newBounds.left));
//            float newY = max(adjustedMarginY, std::min(adjustedMarginY + drawableHeight - newBounds.height, newBounds.top));
//            boba->setPosition(newX, newY);
//        }
//    }
//   
//}

void Gameplay::removeBlock(int index)
{
    if (index >= 0 && index < numBlocks && blocks[index] != nullptr)
    {
        cout << "block is removed in my head just imagine ";
        delete blocks[index];  // Free the memory
        blocks[index] = nullptr;  // Set pointer to nullptr to avoid dangling pointer

    }

    if (!exitDoorVisible && shouldRevealExitDoor(index))
    {
        revealExitDoor();
    }
}
void Gameplay::draw(RenderWindow& window)
{
    if (gameOver)
    {
        //window.draw()
        window.draw(stext);
    }
    if (exitDoorVisible)
    {
        window.draw(exitDoor);
    }
    //window.clear();
    // Draw blocks
    for (int i = 0; i < numBlocks; ++i)
    {
        if (blocks[i] != nullptr && blocks[i]->getexists())
        {
            blocks[i]->draw(window);
        }
    }

    // Draw Boba if it exists
    if (boba != nullptr)
    {
        boba->draw(window);
    }

    // Draw enemies
    for (int i = 0; i < numenemies; ++i)
    {
        if (enemies[i] != nullptr)
        {
            enemies[i]->draw(window);
        }
    }

    window.draw(timerText);
    window.draw(blocksLeftText);
    window.draw(scoret);

    window.display(); // Display the drawn frame
}


void Gameplay::update(RenderWindow& window)
{
    if (gameOver)
    {
        //cout << "game over lol";
    }
    else if (boba != nullptr && !gameOver)
    {
        float speed = 0.5f; // Boba's speed
        // Update the timer
        float elapsedTime = clock.getElapsedTime().asSeconds();
        // Format the time
        stringstream timeStream;
        timeStream << "Time: " << static_cast<int>(elapsedTime);
        timerText.setString(timeStream.str());
        std::stringstream is;
        is << "Bombs Left: " << boba->getnumbombs(); // Adjust according to your method to get bomb count
        blocksLeftText.setString(is.str());

        std::stringstream ib;
        ib << "Score: " << score; // Adjust according to your method to get bomb count
        scoret.setString(ib.str());

        // Handle Boba's movement
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            moveBoba(0, -speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            moveBoba(0, speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            moveBoba(-speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            moveBoba(speed, 0);
        }

        // Drop a new bomb if space is pressed 
        if (Keyboard::isKeyPressed(Keyboard::Space) )
        {
           // cout << "called";
            boba->dropBomb(bombTexture, window);

        }

        // Check for collision between Boba and enemies
        if (checkCollisionWithEnemies())
        {
           delete boba;
            boba = nullptr;
          gameOver = true; // Set game over flag//done in function
            cout << "Boba has disappeared!" << endl;
        }

        // Move enemies randomly
        for (int i = 0; i < numenemies; ++i)
        {
            if (enemies[i] != nullptr)
            {
                moveEnemyRandomly(enemies[i]);
            }
        }

        // Handle bomb explosion if a bomb exists
        if (boba != nullptr && boba->getBomb() != nullptr)
        {
            handleBombExplosion(boba->getBomb(), window);

        }
        // Check if exit door should be visible
        //checkExitDoorVisibility();

        cout << exitDoorVisible;

        checkExitDoorVisibility(); 
        checkBobaExitDoorCollision();

        if (exitDoorVisible)
        {
            //cout << "it should like most def show exitdoor wtf";
            //exitDoor.setColor(sf::Color::White);
            window.clear();
            window.draw(exitDoor);
        }
       
        

    }
   
}

void Gameplay::handleBombExplosion(Bomb* bomb, RenderWindow& window)
{
    if (bomb != nullptr)
    {
        auto currentTime = steady_clock::now();
        auto creationTime = bomb->getCreationTime();
        auto elapsedTime = duration_cast<chrono::seconds>(currentTime - creationTime).count();

        // Only handle explosion if the elapsed time is greater than or equal to the explosion time
        if (elapsedTime >= bomb->getExplosionTime())
        {
            // Bomb explosion handling
            bomb->explode(blocks, numBlocks);

            // Create a list of indices to remove
            vector<int> blocksToRemove;

            for (int i = 0; i < numBlocks; ++i)
            {
                if (blocks[i] != nullptr && blocks[i]->isDestructible())
                {
                    FloatRect blockBounds = blocks[i]->getSprite().getGlobalBounds();
                    FloatRect explosionBounds = bomb->getExplosionBounds();

                    // Check if the block intersects with the explosion bounds
                    bool intersects = !(blockBounds.left > explosionBounds.left + explosionBounds.width ||
                        blockBounds.left + blockBounds.width < explosionBounds.left ||
                        blockBounds.top > explosionBounds.top + explosionBounds.height ||
                        blockBounds.top + blockBounds.height < explosionBounds.top);

                    if (intersects)
                    {
                        DestructibleBlock* destructibleBlock = dynamic_cast<DestructibleBlock*>(blocks[i]);
                        if (destructibleBlock != nullptr)
                        {
                            destructibleBlock->interact();
                            blocksToRemove.push_back(i);
                        }
                    }
                }
            }

            // Remove blocks that were marked for removal
            for (int index : blocksToRemove)
            {
                removeBlock(index);
            }

            // Check if Boba is within the explosion range
            if (boba != nullptr && isBobaInExplosionRange(bomb->getExplosionBounds()))
            {
                delete boba;
                boba = nullptr;
                gameOver = true;
            }

            // Clear the bomb reference
            if (boba != nullptr || numbombs > 0)
            {
                boba->setBomb(nullptr);
            }

            // Debugging output
            cout << "Bomb explosion handled successfully." << endl;

            // Ensure the bomb is handled only once
            delete bomb;
            bomb = nullptr;
        }
    }
}



bool Gameplay::checkCollisionWithEnemies()
{
    if (boba != nullptr)
    {
        FloatRect bobaBounds = boba->getBounds();

        for (int i = 0; i < numenemies; ++i)
        {
            if (enemies[i] != nullptr)
            {
                FloatRect enemyBounds = enemies[i]->getsprite().getGlobalBounds();
                if (bobaBounds.intersects(enemyBounds))
                {
                    return true;
                    gameOver = true;
                }
            }
        }
    }
    return false;
}
void Gameplay::moveEnemyRandomly(Enemy* enemy)
{
    float deltaTime = 0.1f;
    float speed = 15.0f; // Adjust speed as necessary for smoother movement

    // Update the enemy's direction
    enemy->updateDirection(deltaTime);

    // Get the enemy's direction
    int direction = enemy->getdirection();

    // Set movement direction based on the enemy's direction
    float dx = 0.0f;
    float dy = 0.0f;
    switch (direction)
    {
    case 0: dx = -speed * deltaTime; break; // Move left
    case 1: dx = speed * deltaTime; break; // Move right
    case 2: dy = -speed * deltaTime; break; // Move up
    case 3: dy = speed * deltaTime; break; // Move down
    }

    // Get the enemy's current position
    FloatRect currentBounds = enemy->getBounds();
    float currentX = currentBounds.left;
    float currentY = currentBounds.top;

    // Calculate the new position
    float newX = currentX + dx;
    float newY = currentY + dy;

    // Create a FloatRect for the new position
    FloatRect newBounds(newX, newY, currentBounds.width, currentBounds.height);

    // Check for collisions with blocks
    bool collisionDetected = false;
    for (int j = 0; j < numBlocks; ++j)
    {
        if (blocks[j] != nullptr)
        {
            FloatRect blockBounds = blocks[j]->getSprite().getGlobalBounds();
            if (blockBounds.intersects(newBounds))
            {
                collisionDetected = true;
                break;
            }
        }
    }

    // Ensure the enemy stays within the maze boundaries
    if (!collisionDetected)
    {
        if (newX < mazeBounds.left)
            newX = mazeBounds.left;
        if (newX + currentBounds.width > mazeBounds.left + mazeBounds.width)
            newX = mazeBounds.left + mazeBounds.width - currentBounds.width;
        if (newY < mazeBounds.top)
            newY = mazeBounds.top;
        if (newY + currentBounds.height > mazeBounds.top + mazeBounds.height - 50) // Adjust the Y limit
            newY = mazeBounds.top + mazeBounds.height - currentBounds.height - 50;

        // Update the position
        enemy->setPosition(newX, newY);
    }
    else
    {
        // Collision detected, change direction
        int newDirection = rand() % 4; // Generate a new random direction
        enemy->setDirection(newDirection); // Update the enemy's direction
    }
}

//void Gameplay::moveEnemyRandomly(Enemy* enemy)
//{
//    float deltaTime = 0.1f;
//    float speed = 15.0f; // Adjust speed as necessary for smoother movement
//
//    // Update the enemy's direction
//    enemy->updateDirection(deltaTime);
//
//    // Get the enemy's direction
//    int direction = enemy->getdirection();
//
//    // Set movement direction based on the enemy's direction
//    float dx = 0.0f;
//    float dy = 0.0f;
//    switch (direction)
//    {
//    case 0: dx = -speed * deltaTime; break; // Move left
//    case 1: dx = speed * deltaTime; break; // Move right
//    case 2: dy = -speed * deltaTime; break; // Move up
//    case 3: dy = speed * deltaTime; break; // Move down
//    }
//
//    // Get the enemy's current position
//    FloatRect currentBounds = enemy->getBounds();
//    float currentX = currentBounds.left;
//    float currentY = currentBounds.top;
//
//    // Calculate the new position
//    float newX = currentX + dx;
//    float newY = currentY + dy;
//
//    // Create a FloatRect for the new position
//    FloatRect newBounds(newX, newY, currentBounds.width, currentBounds.height);
//
//    // Check for collisions with blocks
//    bool collisionDetected = false;
//    for (int j = 0; j < numBlocks; ++j)
//    {
//        if (blocks[j] != nullptr)
//        {
//            FloatRect blockBounds = blocks[j]->getSprite().getGlobalBounds();
//            if (blockBounds.intersects(newBounds))
//            {
//                collisionDetected = true;
//                break;
//            }
//        }
//    }
//
//    // If there's no collision with blocks, check boundaries and update position
//    if (!collisionDetected)
//    {
//        // Ensure the enemy stays within the maze boundaries
//        if (newX < mazeBounds.left)
//            newX = mazeBounds.left;
//        if (newX + currentBounds.width > mazeBounds.left + mazeBounds.width)
//            newX = mazeBounds.left + mazeBounds.width - currentBounds.width;
//        if (newY < mazeBounds.top)
//            newY = mazeBounds.top;
//        if (newY + currentBounds.height > mazeBounds.top + mazeBounds.height - 50) // Adjust the Y limit
//            newY = mazeBounds.top + mazeBounds.height - currentBounds.height - 50;
//
//        // Update the position
//        enemy->setPosition(newX, newY);
//    }
//    else
//    {
//        // Collision detected, change direction
//        int newDirection = rand() % 4; // Generate a new random direction
//        enemy->setDirection(newDirection); // Update the enemy's direction
//    }
//}

bool Gameplay::isGameOver() 
{

    return gameOver;
}

void Gameplay::checkBobaExitDoorCollision()
{
    if (boba != nullptr)
    {
        FloatRect bobaBounds = boba->getBounds();
        FloatRect exitDoorBounds = exitDoor.getGlobalBounds();
        if (bobaBounds.intersects(exitDoorBounds))
        {
            cout << "ALEXA PLAY BORN TO SHINE BY DILJIT DOSANJH" << endl;

            float blockSize = (std::min(drawableWidth / 16.0f, drawableHeight / 12.0f)) * 1.5f;

            // Alternately call createMaze functions
            static int mazeSequence = 0; // Static variable to keep track of the sequence

            switch (mazeSequence)
            {
            case 0:
                createMaze2(blockSize, blockSize);
                mazeSequence = 1; // Move to the next function
                break;
            case 1:
                createMaze3(blockSize, blockSize);
                mazeSequence = 2; // Move to the next function
                break;
            case 2:
                createMaze(blockSize, blockSize);
                mazeSequence = 0; // Restart the sequence
                break;
            default:
                // Fallback, should not occur
                createMaze2(blockSize, blockSize);
                mazeSequence = 1;
                break;
            }

            score++;
            levelCompleted = true;
        }
    }
}
