#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <vector>
#include <memory>
#include "../Cell.h"
#include "../blocks/Block.h"
#include "../commands/Command.h"

class Command;

class Level : public std::enable_shared_from_this<Level>
{
protected:
    //keep track of number of blocks being placed but haven't ceared a row
    int noClearCounter_ = 0;

    //set counter to 0
    void resetCounter();

    //increment the noClearCounter_ by 1
    void updateCounter();

public:
    //handled by each level
    virtual std::shared_ptr<Block> generateNextBlock() = 0;

    //each level returns its own level number
    virtual int getCurrentLevelNumber() = 0;

    //calculate new points gained after rows being cleared based on rules
    int calculateNewPoints(int rowsCleared);

    //by default it doesnt modify the commands;
    //but for certain levels like lv3 or lv4, we need to add command
    virtual void modifyCommands(std::vector<std::vector<std::shared_ptr<Command>>> &cmds);

    //By default it returns numllptr; which means dont do anything when it returns nullptr
    //but for certain levels like lv4, it returns a ptr to a 1*1 block which should be placed in the board
    virtual std::shared_ptr<Block> handleAfterRowClear(bool isRowCleared);

    virtual void useNoRandomFile(std::string noRandomFile)
    {
        // Default implementation
        return;
    }

    // Setter
    virtual void setIsRandom(bool isRandom)
    {
        // Default implementation
        return;
    }

    // Getter
    virtual bool getIsRandom() const
    {
        // Default implementation
        return true;
    }

    virtual void useBlockSequenceFile(std::string blockSequenceFile) {};
};

#endif