#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
using namespace sf;

class externals
{
private:
    static const int MAX_EXTERNALS = 100; // Adjust based on expected maximum size

    Music dead;
    void initMusic();
    Texture externalsTexture;
    Sprite s_external;
    IntRect rectSource;
    int maxHP;
    int maxlvl;
    int num;
    Font font;
    Text lvlText;
    Text lvlDisplay[MAX_EXTERNALS];
    Vector2f lvlLocation;
    void initText();
    void initVariable();
    void initTexture();
    void initSprite();

    // Replaced vector with arrays
    int currentHP[MAX_EXTERNALS];
    int lvl[MAX_EXTERNALS];
    Sprite externalss[MAX_EXTERNALS];
    int externalCount; // To keep track of the number of current externals

public:
    int table[11][6];
    const Sprite& getSprite(int i) const;
    externals();
    virtual ~externals();
    void spawnexternals(Vector2f position);
    void reduceHP(int i);
    void deletion(Vector2f position);
    void update();
    void updateexternalss();
    void render(RenderTarget& target);
};

// Define the member functions in the corresponding .cpp file
