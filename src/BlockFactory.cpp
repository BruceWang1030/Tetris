#include "../include/BlockFactory.h"
#include <iostream>
using namespace std;

shared_ptr<Block> BlockFactory::createBlock(const string &id)
{
    if (getFactoryMap().find(id) != getFactoryMap().end())
    {
        return getFactoryMap()[id]->create();
    }
    else
    {
        return nullptr;
    }
}
    
BlockFactory::~BlockFactory()
{
}