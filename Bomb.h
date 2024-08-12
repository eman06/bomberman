#include <SFML/Graphics.hpp>
#include <chrono> // For chrono functions
#include"Block.h"
using namespace sf;
using namespace std::chrono;

class Bomb {
public:
    Bomb(const Texture& texture, float x=0, float y=0);

    void setPosition(float x, float y);
    void draw(RenderWindow& window);
    FloatRect getBounds() const;
    FloatRect getExplosionBounds() const;
    bool isActive() const;
    void explode(Block** blocks, int numBlocks);
    bool isExploded() const;

    // Updated methods
    steady_clock::time_point getCreationTime() const;
    float getExplosionTime() const;

private:
    Sprite sprite;
    steady_clock::time_point creationTime; // Time when the bomb was created
    float explosionDelay = 3; // Explosion delay in seconds
};
