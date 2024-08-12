// Enemy.cpp
#include "Enemy.h"

Enemy::Enemy(const Texture& texture, float size, float x=0, float y=0) : size(size), direction(rand() % 4), directionChangeTimer(0.0f)
{
    sprite.setTexture(texture);
    sprite.setScale(size / texture.getSize().x, size / texture.getSize().y);
    sprite.setPosition(x, y);
}

void Enemy::move(float dx, float dy) 
{
    sprite.move(dx, dy);
}

void Enemy::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

FloatRect Enemy::getBounds() const
{
    return sprite.getGlobalBounds();
}

void Enemy::draw(RenderWindow& window) 
{
    window.draw(sprite);
}

void Enemy::setDirection(int newDirection)
{
    direction = newDirection;
}
int Enemy::getdirection()
{
    return direction;
}

void Enemy::updateDirection(float deltaTime) 
{
    directionChangeTimer += deltaTime;
    if (directionChangeTimer >= 1.0f)
    { // Change direction every 1 second
        direction = rand() % 4;
        directionChangeTimer = 0.0f;
    }
}
