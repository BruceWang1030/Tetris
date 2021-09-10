#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "../../include/levels/Level3.h"
#include "../../include/BlockFactory.h"
#include "../../include/CommandFactory.h"
#include <cstdlib>
using namespace std;

Level3::Level3(): isRandom_(true)
{
}

shared_ptr<Block> Level3::generateNextBlock()
{

    if(isRandom_ || noRandomSequence_.size() == 0){
        int newBLockNumber = rand() % 9;
        shared_ptr<Block> newBlock = BlockFactory::createBlock(blockRandomMap_[newBLockNumber]);
        return newBlock;
    } else {
        if(it == noRandomSequence_.end()){
            it = noRandomSequence_.begin();
        }
        string blockType = *(it++);
        shared_ptr<Block> newBlock = BlockFactory::createBlock(blockType + "Block");
        return newBlock;
    }
}

//each level returns its own level number
int Level3::getCurrentLevelNumber()
{
    return 3;
}

void Level3::modifyCommands(vector<vector<shared_ptr<Command>>> &cmds)
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

void Level3::useNoRandomFile(std::string noRandomFile){
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
void Level3::setIsRandom(bool isRandom){
    isRandom_ = isRandom;
}

// Getter
bool Level3::getIsRandom() const{
    return isRandom_;
}