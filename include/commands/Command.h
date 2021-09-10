#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <iostream>
#include "../Gameplay.h"

class Gameplay;

class Command : public std::enable_shared_from_this<Command>
{
public:
    virtual void execute(Gameplay &g) = 0;
    virtual bool isDropCommand()
    {
        return false;
    };
    virtual bool isMovementCommand()
    {
        return false;
    };
    virtual bool isRestartCommand()
    {
        return false;
    };

    virtual void setFileName(const std::string name) {}
    virtual void setBlockType(const std::string type) {}
};

#endif