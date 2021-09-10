#ifndef _BLOCKFACTORY_H_
#define _BLOCKFACTORY_H_

#include <algorithm>
#include <map>
#include <memory>
#include "./blocks/Block.h"

class Block;
class BlockFactoryInitializer;

class BlockFactory
{
    virtual std::shared_ptr<Block> create() = 0;
    static std::map<std::string, std::shared_ptr<BlockFactory>> & getFactoryMap() 
    {
        static std::map<std::string, std::shared_ptr<BlockFactory>> factories_;
        return factories_;
    }

public:
    virtual ~BlockFactory();
    friend class BlockFactoryInitializer;
    static std::shared_ptr<Block> createBlock(const std::string &id);
};

#endif