#ifndef _CLOCKWISE_COMMAND_H_
#define _CLOCKWISE_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class ClockwiseCommand : public Command
{
public:
    void execute(Gameplay &g);
    bool isMovementCommand();

private:
    ClockwiseCommand(){};
    friend class CommandFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public CommandFactory
    {
    public:
        std::shared_ptr<Command> create()
        {
            std::shared_ptr<Command> cmd{new ClockwiseCommand{}};
            return cmd;
        }
        friend class CommandFactoryInitializer;
    };
};

#endif