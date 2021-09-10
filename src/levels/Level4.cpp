#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "../../include/levels/Level4.h"
#include "../../include/BlockFactory.h"
#include "../../include/CommandFactory.h"
#include <cstdlib>
using namespace std;

Level4::Level4()
{
}

shared_ptr<Block> Level4::generateNextBlock()
{
    if (isRandom_ || noRandomSequence_.size() == 0)
    {
        int newBLockNumber = rand() % 9;
        shared_ptr<Block> newBlock = BlockFactory::createBlock(blockRandomMap_[newBLockNumber]);
        return newBlock;
    }
    else
    {
        if (it == noRandomSequence_.end())
        {
            it = noRandomSequence_.begin();
        }
        string blockType = *(it++);
        shared_ptr<Block> newBlock = BlockFactory::createBlock(blockType + "Block");
        return newBlock;
    }
}

//each level returns its own level number
int Level4::getCurrentLevelNumber()
{
    return 4;
}

void Level4::modifyCommands(vector<vector<shared_ptr<Command>>> &cmds)
{
    for (vector<vector<shared_ptr<Command>>>::iterator it = cmds.begin(); it != cmds.end(); ++it)
    {
        if (it->at(0)->isMovementCommand())
        {
            shared_ptr<Command> newHeavyCommand = CommandFactory::createCommand("down");
            it->emplace_back(newHeavyCommand);
        }
    }
    return;
}

shared_ptr<Block> Level4::handleAfterRowClear(bool isRowCleared)
{
    if (isRowCleared)
    {
        resetCounter();
        return nullptr;
    }
    else
    {
        updateCounter();
        if (noClearCounter_ % 5 == 0)
        {
            shared_ptr<Block> newBrownBlock = BlockFactory::createBlock("BBlock");
            return newBrownBlock;
        }
        else
        {
            return nullptr;
        }
    }
}
void Level4::useNoRandomFile(std::string noRandomFile)
{
    {

        //readin all input and convert to vector<shared_ptr<Block>>
        noRandomFile_ = noRandomFile;
        ifstream blockfile(noRandomFile);
        string blockType;
        if (blockfile.is_open())
        {
            while (blockfile >> blockType)
            {
                noRandomSequence_.emplace_back(blockType);
            }
            blockfile.close();
        }
        //set iterator to the first block;
        it = noRandomSequence_.begin();
    }
}

// Setter
void Level4::setIsRandom(bool isRandom)
{
    isRandom_ = isRandom;
}

// Getter
bool Level4::getIsRandom() const
{
    return isRandom_;
}