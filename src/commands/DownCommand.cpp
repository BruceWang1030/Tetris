#include "../../include/commands/DownCommand.h"
using namespace std;

void DownCommand::execute(Gameplay &g)
{
    g.moveDown(g.getCurrBlock());
}

bool DownCommand::isMovementCommand()
{
    return true;
};