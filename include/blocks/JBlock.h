#ifndef _JBLOCK_H_
#define _JBLOCK_H_
#include "Block.h"
#include "../BlockFactory.h"

class Block;
class BlockFactory;

class JBlock : public Block
{
public:
    //overwritten function to return 'J'
    // char getBlockChar();

private:
    //default constructor
    JBlock();

    //BLock Factory
    friend class BlockFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public BlockFactory
    {
    public:
        std::shared_ptr<Block> create()
        {
            std::shared_ptr<Block> blk{new JBlock{}};
            return blk;
        }
        friend class BlockFactoryInitializer;
    };
};

#endif
