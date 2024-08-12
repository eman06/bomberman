
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gameplay.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
    const int STATE_INITIAL_SCREEN = 0;
    const int STATE_RULES_SCREEN = 1;
    const int STATE_GAMEPLAY = 2;
    const int STATE_GAME_OVER = 3;
    
    Clock clock;
    int currentState = STATE_INITIAL_SCREEN;
    bool isGameOver = false;

    VideoMode videoMode = VideoMode::getDesktopMode();
    RenderWindow window(videoMode, "BOBA",Style::Fullscreen);
    int margin = 2*130;
    float drawableWidth = videoMode.width;// -1.5 * 100;
    float drawableHeight = videoMode.height;//-1.5 * 100;
    // Load textures and sprites
    Texture gameOverTexture, bg_texture, destblock, boba_t, hay, tbomb, tenemy, door, spiderverse, gamerules;
    if (!gameOverTexture.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\gameover.png")) {
        cout << "Failed to load game over texture" << endl;
        return -1;
    }
    if (!gamerules.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\gamerules.png")) {
        cout << "Failed to load rules screen texture" << endl;
        return -1;
    }
    if (!spiderverse.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\mainimage.png")) {
        cout << "Failed to load initial screen texture" << endl;
        return -1;
    }
    if (!door.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\thanos hand.png")) {
        cout << "Failed to load door texture" << endl;
    }
    if (!tbomb.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\newbomb.png")) {
        cout << "Failed to load bomb texture" << endl;
    }
    if (!tenemy.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\64253543722.png")) {
        cout << "Failed to load enemy texture" << endl;
    }
    if (!hay.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\redblock.png")) {
        cout << "Failed to load hay texture" << endl;
    }
    if (!destblock.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\blueblock.png")) {
        cout << "Failed to load destructible block texture" << endl;
    }
    if (!boba_t.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\output-onlinepngtools (17).png")) {
        cout << "Failed to load Boba texture" << endl;
    }
    if (!bg_texture.loadFromFile("C:\\Users\\USR\\Downloads\\output-onlinepngtools (10).png")) {
        cout << "Failed to load background texture" << endl;
    }

    Sprite bg_sprite(bg_texture);
    float scaleX = (videoMode.width - 1.5 * 130) / bg_texture.getSize().x;
    float scaleY = (videoMode.height - 1.5 * 130) / bg_texture.getSize().y;
    bg_sprite.setScale(scaleX, scaleY);
    bg_sprite.setPosition((videoMode.width - bg_texture.getSize().x * scaleX) / 2,
        (videoMode.height - bg_texture.getSize().y * scaleY) / 2);

    Sprite grSprite(gamerules);
    grSprite.setScale(1.12 * (videoMode.width / gamerules.getSize().x), 1.8 * (videoMode.height / gamerules.getSize().y));
    grSprite.setPosition((videoMode.width - grSprite.getGlobalBounds().width) / 2,
        (videoMode.height - grSprite.getGlobalBounds().height) / 2);

    Sprite spiderverseSprite(spiderverse);
    spiderverseSprite.setScale((videoMode.width / spiderverse.getSize().x) * 1.65f,
        (videoMode.height / spiderverse.getSize().y) * 1.7f);

    Sprite gameOverSprite(gameOverTexture);
    gameOverSprite.setScale((videoMode.width / gameOverTexture.getSize().x) * 1.65f,
        (videoMode.height / gameOverTexture.getSize().y) * 1.7f);

    Font font;
    if (!font.loadFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\ARIALBD 1.TTF")) {
        cout << "Failed to load font" << endl;
        return -1;
    }

    Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(50);
    timerText.setPosition(window.getSize().x - 1500 - 10.f, 30.0f);
   bool lvlcom = 0;
    // Initialize Gameplay
    Gameplay gameplay(isGameOver,gameOverTexture, bg_texture, destblock, boba_t, hay, tbomb, tenemy, door, margin,
        drawableHeight, drawableWidth, 20, 4,lvlcom, timerText, 0);

    // Load and play music
    Music backgroundMusic;
    if (!backgroundMusic.openFromFile("C:\\Users\\USR\\OneDrive\\Desktop\\boba_images\\Michael Giacchino - Theme (from _Spider Man_) [Original Television Series].ogg")) {
        cout << "Failed to load music file" << endl;
    }
    backgroundMusic.setLoop(true); // Loop the music

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::KeyPressed)
            {
                // Play background music only when transitioning to gameplay
                if (event.key.code == Keyboard::Enter)
                {
                    if (currentState == STATE_INITIAL_SCREEN)
                    {
                        currentState = STATE_RULES_SCREEN;
                    }
                    else if (currentState == STATE_RULES_SCREEN)
                    {
                        currentState = STATE_GAMEPLAY;
                        clock.restart(); // Start the timer when the game begins
                        backgroundMusic.play(); // Start music when gameplay starts
                    }
                    else if (currentState == STATE_GAME_OVER)
                    {
                        currentState = STATE_INITIAL_SCREEN;
                       // isGameOver = false; // Reset the game over flag
                       // gameplay.reset(); // Assuming you have a reset method
                    }
                }
                else if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear();

        if (currentState == STATE_INITIAL_SCREEN)
        {
            window.draw(spiderverseSprite);
        }
        else if (currentState == STATE_GAMEPLAY)
        {
            gameplay.update(window); // Update game state

            // Check if game is over
            if (gameplay.isGameOver()) // Assuming you have a method to check game over state
            {
                window.draw(gameOverSprite);
                isGameOver = true;
                currentState = STATE_GAME_OVER;
            }
            else
            {
                window.draw(bg_sprite);
                gameplay.draw(window); // Draw game objects
            }
        }
        else if (currentState == STATE_RULES_SCREEN)
        {
            window.draw(grSprite);
        }



        window.display();
    }

    return 0;
}
