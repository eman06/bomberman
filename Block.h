
#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Block
{
private:
    Sprite sprite;
    float size;
    bool exists;
    Texture defaultTexture;
    float x; // X position
    float y; // Y position
public:
    Block();
    Block(const Texture& texture, float size, bool e);
    void setPosition(float x, float y);
    void draw(RenderWindow& window);
    Sprite& getSprite(); // Changed to return a reference
    bool checkPosition(float px, float py) const; // Made const
    virtual void interact() = 0;
    void setexists(bool e) { exists = e; }
    bool getexists() const { return exists; }
    virtual bool isDestructible() const = 0;
};
