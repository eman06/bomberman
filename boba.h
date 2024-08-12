




#include <SFML/Graphics.hpp>
#include "Bomb.h"

class Boba 
{
public:
    
    Boba(const sf::Texture& texture, float size, const sf::Texture& bombTexture, int nb);
    ~Boba();
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    FloatRect getBounds() const;
    void dropBomb(const Texture& bombTexture, RenderWindow& window);
    bool isTooCloseToBomb(const Bomb& bomb) const;
    void move(float dx, float dy);
    Bomb* getBomb() const;
    void setBomb(Bomb*  b)
    {
        bomb = b;
    }
    Sprite getsprite()const
    {
        return sprite;
    }
    int getnumbombs()
    {
        return numbomb;
    }
private:

    Sprite sprite;
    Bomb* bomb;
    Texture bombTexture;
    int numbomb;
    float tooCloseDistance = 192.0f; // 3 rows
};

