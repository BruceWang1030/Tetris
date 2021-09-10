#include <iostream>
#include <fstream>
#include <string>
#include "../../include/levels/Level0.h"
#include "../../include/BlockFactory.h"
using namespace std;

Level0::Level0(): blockSequenceFile_("sequence.txt")
{
}

shared_ptr<Block> Level0::generateNextBlock()
{
    if(it == blockSequence_.end()){
        it = blockSequence_.begin();
    }
    string blockType = *(it++);
    shared_ptr<Block> newBlock = BlockFactory::createBlock(blockType + "Block");
    return newBlock;
}

//each level returns its own level number
int Level0::getCurrentLevelNumber()
{
    return 0;
}

void Level0::useBlockSequenceFile(string sequenceFile)
{

    //readin all input and convert to vector<shared_ptr<Block>>
    blockSequenceFile_ = sequenceFile;
    ifstream blockfile(sequenceFile);
    string blockType;
    if (blockfile.is_open())
    {
        while (blockfile >> blockType)
        {
            blockSequence_.emplace_back(blockType);
        }
        blockfile.close();
    }
    //set iterator to the first block;
    it = blockSequence_.begin();
}