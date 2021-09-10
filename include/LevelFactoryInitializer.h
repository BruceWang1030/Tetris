#ifndef _LEVELFACTORYINITIALIZER_H_
#define _LEVELFACTORYINITIALIZER_H_

#include "./levels/Level0.h"
#include "./levels/Level1.h"
#include "./levels/Level2.h"
#include "./levels/Level3.h"
#include "./levels/Level4.h"

#include "LevelFactory.h"

class LevelFactory;
class Level0;
class Level1;
class Level2;
class Level3;
class Level4;

class LevelFactoryInitializer
{
    static LevelFactoryInitializer li;
    LevelFactoryInitializer();
    ~LevelFactoryInitializer();
};

LevelFactoryInitializer LevelFactoryInitializer::li;

#endif