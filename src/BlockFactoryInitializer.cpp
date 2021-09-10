#include "../include/BlockFactoryInitializer.h"
#include "../include/BlockFactory.h"
#include <iostream>
#include <memory>
using namespace std;

BlockFactoryInitializer::BlockFactoryInitializer()
{
    BlockFactory::getFactoryMap()["IBlock"] = make_shared<IBlock::Factory>();
    BlockFactory::getFactoryMap()["JBlock"] = make_shared<JBlock::Factory>();
    BlockFactory::getFactoryMap()["LBlock"] = make_shared<LBlock::Factory>();
    BlockFactory::getFactoryMap()["OBlock"] = make_shared<OBlock::Factory>();
    BlockFactory::getFactoryMap()["SBlock"] = make_shared<SBlock::Factory>();
    BlockFactory::getFactoryMap()["TBlock"] = make_shared<TBlock::Factory>();
    BlockFactory::getFactoryMap()["ZBlock"] = make_shared<ZBlock::Factory>();
    BlockFactory::getFactoryMap()["BBlock"] = make_shared<BBlock::Factory>();
}

BlockFactoryInitializer::~BlockFactoryInitializer() {}