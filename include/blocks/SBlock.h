#ifndef _SBLOCK_H_
#define _SBLOCK_H_
#include "Block.h"
#include "../BlockFactory.h"

class Block;
class BlockFactory;

class SBlock : public Block
{
public:
    //overwritten function to return 'S'
    // char getBlockChar();

private:
    //default constructor
    SBlock();

    //BLock Factory
    friend class BlockFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public BlockFactory
    {
    public:
        std::shared_ptr<Block> create()
        {
            std::shared_ptr<Block> blk{new SBlock{}};
            return blk;
        }
        friend class BlockFactoryInitializer;
    };
};

#endif
