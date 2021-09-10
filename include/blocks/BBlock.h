#ifndef _BBLOCK_H_
#define _BBLOCK_H_
#include "Block.h"
#include "../BlockFactory.h"

class Block;
class BlockFactory;

class BBlock : public Block
{
public:
    //overwritten function to return '*'
    // char getBlockChar();

private:
    //default constructor
    BBlock();

    //BLock Factory
    friend class BlockFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public BlockFactory
    {
    public:
        std::shared_ptr<Block> create()
        {
            std::shared_ptr<Block> blk{new BBlock{}};
            return blk;
        }
        friend class BlockFactoryInitializer;
    };
};

#endif
