#include "../../include/commands/LevelUpCommand.h"
using namespace std;

void LevelUpCommand::execute(Gameplay &g) {
    g.levelUp();
}