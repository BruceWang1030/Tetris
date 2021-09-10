#ifndef _COUNTER_CLOCKWISE_COMMAND_H_
#define _COUNTER_CLOCKWISE_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class CounterClockwiseCommand : public Command
{
public:
    void execute(Gameplay &g);
    bool isMovementCommand();

private:
    CounterClockwiseCommand(){};
    friend class CommandFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public CommandFactory
    {
    public:
        std::shared_ptr<Command> create()
        {
            std::shared_ptr<Command> cmd{new CounterClockwiseCommand{}};
            return cmd;
        }
        friend class CommandFactoryInitializer;
    };
};

#endif