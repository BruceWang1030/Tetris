#ifndef _RESTART_COMMAND_H_
#define _RESTART_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class RestartCommand: public Command {
    public:
        void execute(Gameplay &g);
        bool isRestartCommand(){
            return true;
        };

    private:
        RestartCommand() {};
        friend class CommandFactoryInitializer;

        class Factory;
        friend class Factory;

        class Factory: public CommandFactory {
            public:
            std::shared_ptr<Command> create() {
                std::shared_ptr<Command> cmd{new RestartCommand{}};
                return cmd; 
            }
            friend class CommandFactoryInitializer;
        };
};

#endif