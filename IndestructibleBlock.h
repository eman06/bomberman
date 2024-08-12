#pragma once
// IndestructibleBlock.h
#ifndef INDESTRUCTIBLEBLOCK_H
#define INDESTRUCTIBLEBLOCK_H

#include "Block.h"

class IndestructibleBlock : public Block
{
public:
    IndestructibleBlock(const Texture& texture, float size);
    void interact() override; // Override the interaction method
    bool isDestructible() const override
    {
        return false; // Indestructible blocks are not destructible
    }
};

#endif // INDESTRUCTIBLEBLOCK_H

