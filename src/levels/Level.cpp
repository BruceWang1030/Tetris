#include "../../include/levels/Level.h"
#include <cmath>
using namespace std;

void Level::resetCounter()
{
    noClearCounter_ = 0;
    return;
}

void Level::updateCounter()
{
    noClearCounter_ += 1;
    return;
}

int Level::calculateNewPoints(int rowsCleared)
{
    return pow(getCurrentLevelNumber() + rowsCleared, 2);
}

void Level::modifyCommands(vector<vector<shared_ptr<Command>>> &cmds)
{
    // DEFAULT IMPLEMENTATION
    return;
}

shared_ptr<Block> Level::handleAfterRowClear(bool isRowCleared)
{
    return nullptr;
}