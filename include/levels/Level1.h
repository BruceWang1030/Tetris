#ifndef _LEVEL1_H_
#define _LEVEL1_H_

#include <vector>
#include <string>
#include <memory>
#include <map>
#include "../Cell.h"
#include "../blocks/Block.h"
#include "../LevelFactory.h"
#include "./Level.h"

class Level;
class LevelFactory;

class Level1 : public Level
{
private:
    std::map<int, std::string> blockRandomMap_ = {
        {0, "SBlock"},
        {1, "ZBlock"},
        {2, "IBlock"},
        {3, "IBlock"},
        {4, "JBlock"},
        {5, "JBlock"},
        {6, "LBlock"},
        {7, "LBlock"},
        {8, "OBlock"},
        {9, "OBlock"},
        {10, "TBlock"},
        {11, "TBlock"}};

public:
    //read in the sequence file and stored as a vector of Blocks
    Level1();

    //handled by each level
    std::shared_ptr<Block> generateNextBlock();

    //each level returns its own level number
    int getCurrentLevelNumber();

    //Level Factory
    friend class LevelFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public LevelFactory
    {
    public:
        std::shared_ptr<Level> create()
        {
            std::shared_ptr<Level> lvl{new Level1{}};
            return lvl;
        }
        friend class LevelFactoryInitializer;
    };
};

#endif