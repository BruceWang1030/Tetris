#ifndef _BLOCKFACTORYINITIALIZER_H_
#define _BLOCKFACTORYINITIALIZER_H_

#include "BlockFactory.h"

#include "./blocks/IBlock.h"
#include "./blocks/JBlock.h"
#include "./blocks/LBlock.h"
#include "./blocks/OBlock.h"
#include "./blocks/SBlock.h"
#include "./blocks/TBlock.h"
#include "./blocks/ZBlock.h"
#include "./blocks/BBlock.h"

class BlockFactory;
class IBlock;
class JBlock;
class LBlock;
class OBlock;
class SBlock;
class TBlock;
class ZBlock;
class BBlock;

class BlockFactoryInitializer
{
    static BlockFactoryInitializer bi;
    BlockFactoryInitializer();
    ~BlockFactoryInitializer();
};

BlockFactoryInitializer BlockFactoryInitializer::bi;

#endif