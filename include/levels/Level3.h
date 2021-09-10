#ifndef _LEVEL3_H_
#define _LEVEL3_H_

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

class Level3 : public Level
{
private:
    std::map<int, std::string> blockRandomMap_ = {
        {0, "SBlock"},
        {1, "SBlock"},
        {2, "ZBlock"},
        {3, "ZBlock"},
        {4, "IBlock"},
        {5, "JBlock"},
        {6, "LBlock"},
        {7, "OBlock"},
        {8, "TBlock"}};

    std::string noRandomFile_;
    std::vector<std::string> noRandomSequence_;
    std::vector<std::string>::iterator it;
    bool isRandom_;

public:
    //read in the sequence file and stored as a vector of Blocks
    Level3();

    //handled by each level
    std::shared_ptr<Block> generateNextBlock();

    //each level returns its own level number
    int getCurrentLevelNumber();

    //overriden function of modify commands for game rule "Heavy"
    void modifyCommands(std::vector<std::vector<std::shared_ptr<Command>>> &cmds);

    void useNoRandomFile(std::string noRandomFile);

    // Setter
    void setIsRandom(bool isRandom);

    // Getter
    bool getIsRandom() const;

    //Level Factory
    friend class LevelFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public LevelFactory
    {
    public:
        std::shared_ptr<Level> create()
        {
            std::shared_ptr<Level> lvl{new Level3{}};
            return lvl;
        }
        friend class LevelFactoryInitializer;
    };
};

#endif