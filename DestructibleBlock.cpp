#include "DestructibleBlock.h"
#include <iostream>
using namespace std;

DestructibleBlock::DestructibleBlock(const Texture& texture, float size)
    : Block(texture, size, true) {}

void DestructibleBlock::interact()
{
    cout << "entered interact" << endl;
    setexists(0);
    //delete this;
    //this = nullptr;
}