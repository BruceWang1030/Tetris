#include "../include/LevelFactoryInitializer.h"
#include "../include/LevelFactory.h"
#include "../include/levels/Level0.h"
#include "../include/levels/Level1.h"
#include "../include/levels/Level2.h"
#include "../include/levels/Level3.h"
#include "../include/levels/Level4.h"

#include <iostream>
#include <memory>
using namespace std;

LevelFactoryInitializer::LevelFactoryInitializer()
{
    LevelFactory::getFactoryMap()["Level0"] = make_shared<Level0::Factory>();
    LevelFactory::getFactoryMap()["Level1"] = make_shared<Level1::Factory>();
    LevelFactory::getFactoryMap()["Level2"] = make_shared<Level2::Factory>();
    LevelFactory::getFactoryMap()["Level3"] = make_shared<Level3::Factory>();
    LevelFactory::getFactoryMap()["Level4"] = make_shared<Level4::Factory>();
}

LevelFactoryInitializer::~LevelFactoryInitializer() {}