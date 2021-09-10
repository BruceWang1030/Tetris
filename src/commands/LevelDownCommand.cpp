#include "../../include/commands/LevelDownCommand.h"
using namespace std;

void LevelDownCommand::execute(Gameplay &g) {
    g.levelDown();
}