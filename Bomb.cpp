
#include "Bomb.h"
#include"Block.h"
#include"DestructibleBlock.h"
#include <iostream>
#include <cmath> // For sqrt and pow functions
#include<iostream>
#include"SFML/Graphics.hpp"
using namespace std;
using namespace sf;
using namespace std::chrono;

Bomb::Bomb(const Texture& texture, float x, float y)
{
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    creationTime = steady_clock::now(); // Set creation time to current time
}

void Bomb::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Bomb::draw(RenderWindow& window)
{
    float scaleFactor = 0.51; // Adjust this to make the bomb smaller
    sprite.setScale(scaleFactor, scaleFactor);
    window.draw(sprite);
}

FloatRect Bomb::getBounds() const {
    return sprite.getGlobalBounds();
}

FloatRect Bomb::getExplosionBounds() const
{
    FloatRect bounds = getBounds();
    return FloatRect(bounds.left - 100, bounds.top - 100, bounds.width + 200, bounds.height + 200);
}

bool Bomb::isActive() const
{
    return !isExploded();
}

void Bomb::explode(Block** blocks, int numBlocks)
{
    cout << "Bomb exploded!" << endl;
    Color c(255, 255, 255, 128);
    sprite.setColor(c);
    FloatRect bombBounds = getExplosionBounds();
    float bombX = bombBounds.left + bombBounds.width / 2;
    float bombY = bombBounds.top + bombBounds.height / 2;

    float explosionRadius = 64.0f; // Assuming explosion affects a radius of 64 units

    for (int i = 0; i < numBlocks; i++)
    {
        if (blocks[i] != nullptr && blocks[i]->getexists())
        {
            FloatRect blockBounds = blocks[i]->getSprite().getGlobalBounds();
            float blockX = blockBounds.left + blockBounds.width / 2;
            float blockY = blockBounds.top + blockBounds.height / 2;

            float distance = sqrt(pow(bombX - blockX, 2) + pow(bombY - blockY, 2));
            if (distance <= explosionRadius)
            {
                if (DestructibleBlock* destructibleBlock = dynamic_cast<DestructibleBlock*>(blocks[i]))
                {
                    if (blocks[i]->isDestructible())
                    {
                        cout << "Destructible block destroyed!" << endl;
                        blocks[i]->interact();
                    }
                }
            }
        }
    }
}

bool Bomb::isExploded() const
{
    auto currentTime = steady_clock::now();
    auto elapsedTime = duration_cast<chrono::seconds>(currentTime - creationTime).count();
    return elapsedTime >= explosionDelay;
}

// Updated methods
steady_clock::time_point Bomb::getCreationTime() const {
    return creationTime;
}

float Bomb::getExplosionTime() const {
    return explosionDelay;
}
