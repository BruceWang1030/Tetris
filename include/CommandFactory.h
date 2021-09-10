#ifndef _COMMANDFACTORY_H_
#define _COMMANDFACTORY_H_

#include <algorithm>
#include <map>
#include <memory>
#include "./commands/Command.h"

class Command;
class CommandFactoryInitializer;

class CommandFactory
{
    virtual std::shared_ptr<Command> create() = 0;
    static std::map<std::string, std::shared_ptr<CommandFactory>> &getFactoryMap()
    {
        static std::map<std::string, std::shared_ptr<CommandFactory>> factories_;
        return factories_;
    }

public:
    virtual ~CommandFactory() {}
    friend class CommandFactoryInitializer;

    static std::shared_ptr<Command> createCommand(const std::string &id)
    {
        if (getFactoryMap().find(id) != getFactoryMap().end())
        {
            return getFactoryMap()[id]->create();
        }
        else
        {
            return nullptr;
        }
    }
};

#endif