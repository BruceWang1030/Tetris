#include "../../include/commands/BlockTypeCommand.h"
using namespace std;

void BlockTypeCommand::execute(Gameplay &g){
    string blockType = getBlockType();
    g.generateBlock(blockType);
}