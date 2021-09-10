#include "../../include/commands/RestartCommand.h"
using namespace std;

void RestartCommand::execute(Gameplay &g) {
    g.restart();
}