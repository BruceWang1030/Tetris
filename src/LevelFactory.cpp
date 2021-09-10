#include "../include/LevelFactory.h"
#include <iostream>
using namespace std;

shared_ptr<Level> LevelFactory::createLevel(const string &id)
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
    
LevelFactory::~LevelFactory()
{
}
