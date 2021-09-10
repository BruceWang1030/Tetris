#ifndef _HINTGENERATOR_H_
#define _HINTGENERATOR_H_

#include <memory>
#include "./Gameplay.h"
#include "./blocks/Block.h"

class Gameplay;

// Nested class to generate hints
class HintGenerator
{
    // Helper method to give a score for each drop location
    int calculateScore(Gameplay*, std::shared_ptr<Block>);
public:
    void generateHint(Gameplay*);
    // takes: a Gameplay
    // modifies: the Gameplay
    // ensures: a Hint Block is created and the lowest score drop location is set on the Hint Block
};

#endif