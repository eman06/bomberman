
#include "Boba.h"
#include <iostream>
#include <cmath> // For sqrt and pow functions

using namespace std;
using namespace sf;

Boba::Boba(const Texture& texture, float size, const Texture& bombTexture, int nb)
    : numbomb(nb), bomb(nullptr), bombTexture(bombTexture) {
    sprite.setTexture(texture);
    sprite.setScale(size / texture.getSize().x, size / texture.getSize().y);
}

void Boba::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}
void Boba::draw(RenderWindow& window)
{
    window.draw(sprite);
    if (bomb != nullptr && !bomb->isExploded())
    {
        bomb->draw(window);
    }
}


FloatRect Boba::getBounds() const {
    return sprite.getGlobalBounds();
}

void Boba::dropBomb(const Texture& bombTexture, RenderWindow& window)
{
    if (bomb == nullptr && numbomb > 0)
    {
       // cout << "bomb drawn";
        bomb = new Bomb(bombTexture, sprite.getPosition().x, sprite.getPosition().y);
        numbomb--;
    }
}

bool Boba::isTooCloseToBomb(const Bomb& bomb) const
{
    FloatRect bobaBounds = getBounds();
    FloatRect bombBounds = bomb.getBounds();
    float distance = sqrt(pow(bobaBounds.left + bobaBounds.width / 2 - (bombBounds.left + bombBounds.width / 2), 2) +
        pow(bobaBounds.top + bobaBounds.height / 2 - (bombBounds.top + bombBounds.height / 2), 2));
    return distance < tooCloseDistance;
}

Bomb* Boba::getBomb() const
{
    return bomb;
}

Boba::~Boba() {
    delete bomb; // Clean up dynamically allocated Bomb if it exists
}

void Boba::move(float dx, float dy) {
    sprite.move(dx, dy);
}