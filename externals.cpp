#include "externals.h"
#include <iostream> // For std::cout
using namespace std;

void externals::initMusic()
{
    if (!dead.openFromFile("Music/hurt.mp3"))
    {
        cout << "Hurt-ERROR" << endl;
    }
}

void externals::initText()
{
    if (!font.loadFromFile("Font/pixel.ttf"))
    {
        cout << "FontError" << endl;
    }
    lvlText.setFont(font);
    lvlText.setString("1");
    lvlText.setCharacterSize(30);
}

void externals::initVariable()
{
    this->rectSource = IntRect(0, 0, 13, 22);
    this->maxHP = 15;
    this->maxlvl = 5;
    this->externalCount = 0; // Initialize externalCount to 0
}

void externals::initTexture()
{
    if (!this->externalsTexture.loadFromFile("Texture/externals.png"))
    {
        cout << "externals-ERROR";
    }
}

void externals::initSprite()
{
    this->s_external.setTexture(this->externalsTexture);
    this->s_external.setTextureRect(rectSource);
}

const Sprite& externals::getSprite(int i) const
{
    if (i >= 0 && i < externalCount)
    {
        return this->externalss[i];
    }
    throw out_of_range("Index out of range");
}

externals::externals()
{
    this->initMusic();
    this->initText();
    this->initVariable();
    this->initTexture();
    this->initSprite();
}

externals::~externals()
{
}

void externals::spawnexternals(Vector2f position)
{
    int xIndex = static_cast<int>(position.x / 192);
    int yIndex = static_cast<int>((position.y - 369) / 142);

    if (this->table[xIndex][yIndex] != 1)
    {
        if (externalCount >= MAX_EXTERNALS) {
            cout << "Exceeded maximum number of externals" << endl;
            return;
        }

        this->s_external.setPosition(position.x + 76.25f, position.y + 32.5f);
        this->table[xIndex][yIndex] = 1;
        float scaleFactor = 2.5f; // Increase width by a factor of 2
        s_external.setScale(Vector2f(scaleFactor, scaleFactor));

        this->lvlLocation.x = position.x + 10.f;
        this->lvlLocation.y = position.y + 80.f;

        this->lvlText.setPosition(this->lvlLocation);

        this->lvlDisplay[externalCount] = this->lvlText;

        this->currentHP[externalCount] = maxHP;
        this->lvl[externalCount] = 1;
        this->externalss[externalCount] = this->s_external;

        externalCount++;
    }
    else
    {
        for (int i = 0; i < externalCount; i++)
        {
            if (this->externalss[i].getPosition().x == position.x + 76.25f &&
                this->externalss[i].getPosition().y == position.y + 32.5f &&
                this->lvl[i] < 5)
            {
                this->lvl[i] += 1;
                this->lvlDisplay[i].setString(to_string(this->lvl[i]));
                if (this->lvl[i] < 5)
                {
                    this->currentHP[i] = 12 + 3 * this->lvl[i];
                }
                else
                {
                    this->currentHP[i] = 30;
                }
                cout << this->currentHP[i] << endl;
                break;
            }
        }
    }
}

void externals::reduceHP(int i)
{
    if (i >= 0 && i < externalCount) {
        currentHP[i] -= 1;
        if (currentHP[i] <= 0)
        {
            this->dead.play();
            deletion(this->externalss[i].getPosition());
        }
    }
    else {
        throw out_of_range("Index out of range");
    }
}

void externals::deletion(Vector2f position)
{
    this->num -= 1;
    for (int i = 0; i < externalCount; i++)
    {
        if (this->externalss[i].getPosition() == position)
        {
            this->table[static_cast<int>((position.x - 76.25f) / 192)]
                [static_cast<int>((position.y - 401.5f) / 142)] = 0;

            for (int j = i; j < externalCount - 1; j++)
            {
                this->currentHP[j] = this->currentHP[j + 1];
                this->lvl[j] = this->lvl[j + 1];
                this->lvlDisplay[j] = this->lvlDisplay[j + 1];
                this->externalss[j] = this->externalss[j + 1];
            }
            externalCount--;
            break;
        }
    }
}

void externals::update()
{
    updateexternalss();
}

void externals::updateexternalss()
{
    for (int i = 0; i < externalCount; i++)
    {
        externalss[i].setTextureRect(rectSource);
    }
}

void externals::render(RenderTarget& target)
{
    for (int i = 0; i < externalCount; i++)
    {
        target.draw(externalss[i]);
    }
    for (int i = 0; i < externalCount; i++)
    {
        target.draw(lvlDisplay[i]);
    }
}
