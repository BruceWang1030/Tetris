#include "../../include/commands/LeftCommand.h"
using namespace std;

void LeftCommand::execute(Gameplay &g)
{
    g.moveLeft(g.getCurrBlock());
}

bool LeftCommand::isMovementCommand()
{
    return true;
};