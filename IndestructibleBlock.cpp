#include "IndestructibleBlock.h"
#include "IndestructibleBlock.h"
#include <iostream>
using namespace std;

IndestructibleBlock::IndestructibleBlock(const Texture& texture, float size)
    : Block(texture, size, true)
{
    // Additional initialization if needed
}

void IndestructibleBlock::interact()
{
    cout << "Indestructible block cannot be destroyed!" << endl;
    // No action needed, as this block cannot be destroyed
}