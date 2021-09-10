#ifndef _HINT_COMMAND_H_
#define _HINT_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class HintCommand: public Command {
    public:
        void execute(Gameplay &g);
    
    private:
        HintCommand() {};
        friend class CommandFactoryInitializer;

        class Factory;
        friend class Factory;

        class Factory: public CommandFactory {
            public:
            std::shared_ptr<Command> create() {
                std::shared_ptr<Command> cmd{new HintCommand{}};
                return cmd; 
            }
            friend class CommandFactoryInitializer;
        };
        
};

#endif