#ifndef _AIMODE_COMMAND_H_
#define _AIMODE_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class AIModeCommand : public Command
{
public:
    void execute(Gameplay &g);

private:
    AIModeCommand(){};
    friend class CommandFactoryInitializer;

    class Factory;
    friend class Factory;

    class Factory : public CommandFactory
    {
    public:
        std::shared_ptr<Command> create()
        {
            std::shared_ptr<Command> cmd{new AIModeCommand{}};
            return cmd;
        }
        friend class CommandFactoryInitializer;
    };
};

#endif