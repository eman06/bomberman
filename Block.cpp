

#include "Block.h"
#include <iostream>

using namespace std;

Block::Block() : size(0.0f), x(0), y(0), exists(false)
{
    if (!defaultTexture.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\destbrick.png"))
    {
        cout << "Failed to load default block texture" << endl;
    }
    sprite.setTexture(defaultTexture);
    sprite.setPosition(x, y);
    // Ensure size is not zero before scaling
    if (size > 0.0f) 
    {
        sprite.setScale(size / defaultTexture.getSize().x, size / defaultTexture.getSize().y);
    }
}

Block::Block(const Texture& texture, float size, bool e) : size(size), exists(e), x(100), y(100)
{
    sprite.setTexture(texture);
    if (size > 0.0f) 
    {
        sprite.setScale(size / texture.getSize().x, size / texture.getSize().y);
    }
}

void Block::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
    sprite.setPosition(x, y);
}

bool Block::checkPosition(float px, float py) const
{
    FloatRect bounds = sprite.getGlobalBounds();
    return (px >= bounds.left && px <= bounds.left + bounds.width &&
        py >= bounds.top && py <= bounds.top + bounds.height && exists);
}

void Block::draw(RenderWindow& window)
{
    if (exists) // Only draw if the block exists
    {
        //cout << "ONE DAY I HEARD THE WORD VAAATHAWARANN";
        window.draw(sprite);
    }
}

Sprite& Block::getSprite()
{
    return this->sprite;
}
