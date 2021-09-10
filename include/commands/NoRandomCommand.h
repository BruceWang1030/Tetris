#ifndef _NORANDOM_COMMAND_H_
#define _NORANDOM_COMMAND_H_

#include "../Gameplay.h"
#include "Command.h"
#include "../CommandFactory.h"

class Gameplay;
class CommandFactory;
class Command;

class NoRandomCommand: public Command {

    public:
        void execute(Gameplay &g);

        void setFileName(const std::string name) override { fileName_ = name; }
        std::string getFileName() const { return fileName_; }
        
    private:
        NoRandomCommand() {};
        friend class CommandFactoryInitializer;

        std::string fileName_;

        class Factory;
        friend class Factory;

        class Factory: public CommandFactory {
            public:
            std::shared_ptr<Command> create() {
                std::shared_ptr<Command> cmd{new NoRandomCommand{}};
                return cmd; 
            }
            friend class CommandFactoryInitializer;
        };
};

#endif