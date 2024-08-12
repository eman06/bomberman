#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Enemy 
{

private:
    Sprite sprite;
    float size;
    int direction; // 0: left, 1: right, 2: up, 3: down
    float directionChangeTimer; // Timer to control direction change


public:
    Enemy(const Texture& texture, float size, float x, float y);
    void move(float dx, float dy);
    void setPosition(float x, float y);
    FloatRect getBounds() const;
    void draw(RenderWindow& window);
    Sprite getsprite()const
    {
        return sprite;
    }
    void setDirection(int newDirection);
    void updateDirection(float deltaTime); // To update direction periodically
    int getdirection();
    //void updateDirection(float deltaTime); // Update direction based on time

};
