#ifndef _LEVEL0_H_
#define _LEVEL0_H_

#include <vector>
#include <string>
#include <memory>

#include "../Cell.h"
#include "../blocks/Block.h"
#include "../LevelFactory.h"
#include "./Level.h"

class Level;
class LevelFactory;

class Level0 : public Level
{
private:
    std::string blockSequenceFile_;
    std::vector<std::string> blockSequence_;
    std::vector<std::string>::iterator it;

public:
    //read in the sequence file and stored as a vector of Blocks
    Level0();

    //handled by each level
    std::shared_ptr<Block> generateNextBlock();

    //each level returns its own level number
    int getCurrentLevelNumber();

    //Setters
    void useBlockSequenceFile(std::string blockSequenceFile) override;

    //Level Factory
    friend class LevelFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public LevelFactory
    {
    public:
        std::shared_ptr<Level> create()
        {
            std::shared_ptr<Level> lvl{new Level0{}};
            return lvl;
        }
        friend class LevelFactoryInitializer;
    };
};

#endif