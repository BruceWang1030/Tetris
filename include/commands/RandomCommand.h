#ifndef _RANDOM_COMMAND_H_
#define _RANDOM_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class RandomCommand: public Command {
    public:
        void execute(Gameplay &g);

    private:
        RandomCommand() {};
        friend class CommandFactoryInitializer;

        class Factory;
        friend class Factory;

        class Factory: public CommandFactory {
            public:
            std::shared_ptr<Command> create() {
                std::shared_ptr<Command> cmd{new RandomCommand{}};
                return cmd; 
            }
            friend class CommandFactoryInitializer;
        };
        
};

#endif