#ifndef _BLOCKTYPE_COMMAND_H_
#define _BLOCKTYPE_COMMAND_H_

#include <string>
#include <memory>
#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class BlockTypeCommand : public Command
{
public:
    void execute(Gameplay &g);

    void setBlockType(const std::string type) override { blockType_ = type; }
    std::string getBlockType() const { return blockType_; }

private:
    BlockTypeCommand(){};
    friend class CommandFactoryInitializer;

    std::string blockType_;

    class Factory;
    friend class Factory;

    class Factory : public CommandFactory
    {
    public:
        std::shared_ptr<Command> create()
        {
            std::shared_ptr<Command> cmd{new BlockTypeCommand{}};
            return cmd;
        }
        friend class CommandFactoryInitializer;
    };
};

#endif