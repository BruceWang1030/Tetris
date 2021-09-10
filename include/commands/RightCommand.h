#ifndef _RIGHT_COMMAND_H_
#define _RIGHT_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class RightCommand : public Command
{
public:
    void execute(Gameplay &g);
    bool isMovementCommand();

private:
    RightCommand(){};
    friend class CommandFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public CommandFactory
    {
    public:
        std::shared_ptr<Command> create()
        {
            std::shared_ptr<Command> cmd{new RightCommand{}};
            return cmd;
        }
        friend class CommandFactoryInitializer;
    };
};

#endif