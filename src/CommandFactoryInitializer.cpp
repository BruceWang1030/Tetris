#include <iostream>
#include <memory>
#include "../include/CommandFactoryInitializer.h"

using namespace std;

CommandFactoryInitializer::CommandFactoryInitializer()
{

    /* Moves */

    CommandFactory::getFactoryMap()["left"] = std::make_shared<LeftCommand::Factory>();
    CommandFactory::getFactoryMap()["right"] = std::make_shared<RightCommand::Factory>();
    CommandFactory::getFactoryMap()["down"] = std::make_shared<DownCommand::Factory>();
    CommandFactory::getFactoryMap()["clockwise"] = std::make_shared<ClockwiseCommand::Factory>();
    CommandFactory::getFactoryMap()["counterclockwise"] = std::make_shared<CounterClockwiseCommand::Factory>();
    CommandFactory::getFactoryMap()["drop"] = std::make_shared<DropCommand::Factory>();

    /* Levels */

    CommandFactory::getFactoryMap()["levelup"] = std::make_shared<LevelUpCommand::Factory>();
    CommandFactory::getFactoryMap()["leveldown"] = std::make_shared<LevelDownCommand::Factory>();

    CommandFactory::getFactoryMap()["norandom"] = std::make_shared<NoRandomCommand::Factory>();
    CommandFactory::getFactoryMap()["random"] = std::make_shared<RandomCommand::Factory>();
    CommandFactory::getFactoryMap()["blocktype"] = std::make_shared<BlockTypeCommand::Factory>();
    CommandFactory::getFactoryMap()["restart"] = std::make_shared<RestartCommand::Factory>();
    CommandFactory::getFactoryMap()["hint"] = std::make_shared<HintCommand::Factory>();

    /* Bonus */
    CommandFactory::getFactoryMap()["aimode"] = std::make_shared<AIModeCommand::Factory>();
 
}

CommandFactoryInitializer::~CommandFactoryInitializer(){}
