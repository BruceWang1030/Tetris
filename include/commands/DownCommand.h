#ifndef _DOWN_COMMAND_H_
#define _DOWN_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class DownCommand : public Command
{
public:
    void execute(Gameplay &g);
    bool isMovementCommand();

private:
    DownCommand(){};
    friend class CommandFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public CommandFactory
    {
    public:
        std::shared_ptr<Command> create()
        {
            std::shared_ptr<Command> cmd{new DownCommand{}};
            return cmd;
        }
        friend class CommandFactoryInitializer;
    };
};

#endif