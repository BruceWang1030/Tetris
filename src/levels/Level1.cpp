#include <iostream>
#include <fstream>
#include <string>
#include "../../include/levels/Level1.h"
#include "../../include/BlockFactory.h"
#include <cstdlib>
using namespace std;

Level1::Level1()
{
}

shared_ptr<Block> Level1::generateNextBlock()
{
    int newBLockNumber = rand() % 12;
    shared_ptr<Block> newBlock = BlockFactory::createBlock(blockRandomMap_[newBLockNumber]);
    return newBlock;
}

//each level returns its own level number
int Level1::getCurrentLevelNumber()
{
    return 1;
}
