#include "../../include/commands/HintCommand.h"
using namespace std;

void HintCommand::execute(Gameplay &g) {
    g.generateHint();
}