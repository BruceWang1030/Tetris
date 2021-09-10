#include "../../include/commands/NoRandomCommand.h"
using namespace std;

void NoRandomCommand::execute(Gameplay &g) {
    string fileName = getFileName();
    g.noRandom(fileName);
}