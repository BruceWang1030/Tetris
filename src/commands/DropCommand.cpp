#include "../../include/commands/DropCommand.h"
using namespace std;

void DropCommand::execute(Gameplay &g)
{
    g.dropBlock();
}

bool DropCommand::isDropCommand()
{
    return true;
};