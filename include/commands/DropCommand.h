#ifndef _DROP_COMMAND_H_
#define _DROP_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class DropCommand : public Command
{
public:
    void execute(Gameplay &g);
    bool isDropCommand();

private:
    DropCommand(){};
    friend class CommandFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public CommandFactory
    {
    public:
        std::shared_ptr<Command> create()
        {
            std::shared_ptr<Command> cmd{new DropCommand{}};
            return cmd;
        }
        friend class CommandFactoryInitializer;
    };
};

#endif