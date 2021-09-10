#ifndef _COMMANDFACTORYINITIALIZER_H_
#define _COMMANDFACTORYINITIALIZER_H_

#include <memory>
#include "CommandFactory.h"

/* Commands */
#include "./commands/LeftCommand.h"
#include "./commands/RightCommand.h"
#include "./commands/DownCommand.h"
#include "./commands/ClockwiseCommand.h"
#include "./commands/CounterClockwiseCommand.h"
#include "./commands/DropCommand.h"
#include "./commands/LevelUpCommand.h"
#include "./commands/LevelDownCommand.h"
#include "./commands/NoRandomCommand.h"
#include "./commands/RandomCommand.h"
#include "./commands/BlockTypeCommand.h"
#include "./commands/RestartCommand.h"
#include "./commands/HintCommand.h"
#include "./commands/AIModeCommand.h"

class CommandFactory;
class LeftCommand;
class RightCommand;
class DownCommand;
class ClockwiseCommand;
class CounterClockwiseCommand;
class DropCommand;
class LevelUpCommand;
class LevelDownCommand;
class NoRandomCommand;
class RandomCommand;
class BlockTypeCommand;
class RestartCommand;
class HintCommand;
class AIModeCommand;

class CommandFactoryInitializer
{
    static CommandFactoryInitializer ci;
    CommandFactoryInitializer();
    ~CommandFactoryInitializer();
};

CommandFactoryInitializer CommandFactoryInitializer::ci;

#endif