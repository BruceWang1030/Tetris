#ifndef _OBLOCK_H_
#define _OBLOCK_H_
#include "Block.h"
#include "../BlockFactory.h"

class Block;
class BlockFactory;

class OBlock : public Block
{
public:
    //overwritten function to return 'O'
    // char getBlockChar();

private:
    //default constructor
    OBlock();

    //BLock Factory
    friend class BlockFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public BlockFactory
    {
    public:
        std::shared_ptr<Block> create()
        {
            std::shared_ptr<Block> blk{new OBlock{}};
            return blk;
        }
        friend class BlockFactoryInitializer;
    };
};

#endif
