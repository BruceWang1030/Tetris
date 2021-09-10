#ifndef _IBLOCK_H_
#define _IBLOCK_H_
#include "Block.h"
#include "../BlockFactory.h"

class Block;
class BlockFactory;

class IBlock : public Block
{
public:
    //overwritten function to return 'I'
    // char getBlockChar();

private:
    //default constructor
    IBlock();

    //BLock Factory
    friend class BlockFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public BlockFactory
    {
    public:
        std::shared_ptr<Block> create()
        {
            std::shared_ptr<Block> blk{new IBlock{}};
            return blk;
        }
        friend class BlockFactoryInitializer;
    };
};

#endif
