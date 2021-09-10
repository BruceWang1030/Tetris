#ifndef _TBLOCK_H_
#define _TBLOCK_H_
#include "Block.h"
#include "../BlockFactory.h"

class Block;
class BlockFactory;

class TBlock : public Block
{
public:
    //overwritten function to return 'T'
    // char getBlockChar();

private:
    //default constructor
    TBlock();

    //BLock Factory
    friend class BlockFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public BlockFactory
    {
    public:
        std::shared_ptr<Block> create()
        {
            std::shared_ptr<Block> blk{new TBlock{}};
            return blk;
        }
        friend class BlockFactoryInitializer;
    };
};

#endif
