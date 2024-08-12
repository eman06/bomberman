#pragma once
#include"Block.h"
class DestructibleBlock : public Block
{
public:
    DestructibleBlock(const Texture& texture, float size);
    void interact() override; // Override the interaction method
    bool isDestructible() const override
    {
        return true; // Destructible blocks are destructible
    }
};

