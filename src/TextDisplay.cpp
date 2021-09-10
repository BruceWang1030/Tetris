#include <iostream>
#include <string>
#include "vector"
#include "../include/TextDisplay.h"

using namespace std;

TextDisplay::TextDisplay(ostream &out, shared_ptr<Gameplay> game) : output(out)
{
    subject = game;
}

TextDisplay::~TextDisplay()
{
}

void TextDisplay::notify()
{
    if (subject->isGameOver())
    {
        return;
    }
    shared_ptr<Board> gameBoard = subject->getBoardState();
    shared_ptr<Scoreboard> scoreboard = subject->getScoreboard();

    output << "Level:      " << subject->getLevel()->getCurrentLevelNumber() << endl;
    output << "Score:      " << scoreboard->getScore() << endl;
    output << "Hi Score:   " << scoreboard->getHighScore() << endl;
    output << *gameBoard << endl;
    output << "Next:" << endl;
    output << *(subject->getNextBlock());
}
