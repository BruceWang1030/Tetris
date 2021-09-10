#ifndef _LEFT_COMMAND_H_
#define _LEFT_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class LeftCommand : public Command
{
public:
    void execute(Gameplay &g);
    bool isMovementCommand();

private:
    LeftCommand(){};
    friend class CommandFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public CommandFactory
    {
    public:
        std::shared_ptr<Command> create()
        {
            std::shared_ptr<Command> cmd{new LeftCommand{}};
            return cmd;
        }
        friend class CommandFactoryInitializer;
    };
};

#endif