#include "../../include/commands/CounterClockwiseCommand.h"
using namespace std;

void CounterClockwiseCommand::execute(Gameplay &g)
{
    g.rotateCounterClockwise();
}

bool CounterClockwiseCommand::isMovementCommand()
{
    return true;
};