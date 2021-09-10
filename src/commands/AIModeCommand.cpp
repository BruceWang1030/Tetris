#include "../../include/commands/AIModeCommand.h"
using namespace std;

void AIModeCommand::execute(Gameplay &g){
    g.setAIMode(true);
}