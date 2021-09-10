#include <iostream>
#include <fstream>
#include <string>
#include "../../include/levels/Level2.h"
#include "../../include/BlockFactory.h"
#include <cstdlib>
using namespace std;

Level2::Level2()
{
}

shared_ptr<Block> Level2::generateNextBlock()
{
    int newBLockNumber = rand() % 7;
    shared_ptr<Block> newBlock = BlockFactory::createBlock(blockRandomMap_[newBLockNumber]);
    return newBlock;
}

//each level returns its own level number
int Level2::getCurrentLevelNumber()
{
    return 2;
}
