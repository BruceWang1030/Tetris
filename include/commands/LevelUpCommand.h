#ifndef _LEVELUP_COMMAND_H_
#define _LEVELUP_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class LevelUpCommand: public Command {
    public:
        void execute(Gameplay &g);

    private:
        LevelUpCommand() {};
        friend class CommandFactoryInitializer;

        class Factory;
        friend class Factory;

        class Factory: public CommandFactory {
            public:
            std::shared_ptr<Command> create() {
                std::shared_ptr<Command> cmd{new LevelUpCommand{}};
                return cmd; 
            }
            friend class CommandFactoryInitializer;
        };
};

#endif