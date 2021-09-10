#include "../../include/commands/RightCommand.h"
using namespace std;

void RightCommand::execute(Gameplay &g)
{
    g.moveRight(g.getCurrBlock());
}

bool RightCommand::isMovementCommand()
{
    return true;
};