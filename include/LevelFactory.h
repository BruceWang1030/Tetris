#ifndef _LEVELFACTORY_H_
#define _LEVELFACTORY_H_

#include <algorithm>
#include <map>
#include <memory>
#include "./levels/Level.h"

class Level;
class LevelFactoryInitializer;

class LevelFactory
{
    virtual std::shared_ptr<Level> create() = 0;
    static std::map<std::string, std::shared_ptr<LevelFactory>> & getFactoryMap() 
    {
        static std::map<std::string, std::shared_ptr<LevelFactory>> factories_;
        return factories_;
    }

public:
    virtual ~LevelFactory();
    friend class LevelFactoryInitializer;
    static std::shared_ptr<Level> createLevel(const std::string &id);
};

#endif