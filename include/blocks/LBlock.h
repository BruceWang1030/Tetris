#ifndef _LBLOCK_H_
#define _LBLOCK_H_
#include "Block.h"
#include "../BlockFactory.h"

class Block;
class BlockFactory;

class LBlock : public Block
{
public:
    //overwritten function to return 'L'
    // char getBlockChar();

private:
    //default constructor
    LBlock();

    //BLock Factory
    friend class BlockFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public BlockFactory
    {
    public:
        std::shared_ptr<Block> create()
        {
            std::shared_ptr<Block> blk{new LBlock{}};
            return blk;
        }
        friend class BlockFactoryInitializer;
    };
};

#endif
