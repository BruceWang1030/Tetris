#include "../../include/commands/ClockwiseCommand.h"
using namespace std;

void ClockwiseCommand::execute(Gameplay &g)
{
    g.rotateClockwise();
}

bool ClockwiseCommand::isMovementCommand()
{
    return true;
};