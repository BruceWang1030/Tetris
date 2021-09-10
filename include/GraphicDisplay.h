#ifndef _GRAPHICDISPLAY_H_
#define _GRAPHICDISPLAY_H_

#include <memory>
#include <map>
#include <string>
#include "Gameplay.h"
#include "./Observer.h"
#include "XDisplay.h"
#include "../include/Board.h"
#include "../include/blocks/Block.h"


class GraphicDisplay : public Observer
{
private:

    // Cell information (size and amount)
    const int cellSize = 15;
    const int row = 18;
    const int column = 11;

    // Board details (dimensions + location)
    const int boardWidth = cellSize * column;
    const int boardHeight = cellSize * row;
    const int boardxCoord = 25;
    const int boardyCoord = 100;

    // Window dimensions
    const int width = boardWidth + 50;
    const int height = boardHeight + 200;

    // Map for the char of the block to the colour on the display
    std::map<char, std::string> blockToColour = {
        {'I', "red"}, 
        {'J', "green"}, 
        {'L', "blue"}, 
        {'O', "cyan"}, 
        {'S', "yellow"}, 
        {'Z', "magenta"}, 
        {'T', "orange"}, 
        {'*', "brown"},
        {' ', "white"},
        {'?', "black"}
    };

    // The observer pattern subject and the X11/Xlib display
    std::shared_ptr<Gameplay> subject;
    Xdisplay xDisplay_;

    // Current State
    std::shared_ptr<Board> currGameBoard_ = nullptr;
    std::shared_ptr<Block> currNextBlock_ = nullptr;
    int currLevel_ = -1;
    int currScore_ = -1;
    int currHighScore_ = -1;

    // Helper method to draw the game Board in XWindow
    void drawBoard(std::shared_ptr<Board> gameBoard);
    
public:
    GraphicDisplay(std::shared_ptr<Gameplay> game);
    // takes: a Gameplay pointer (subject of the observer pattern)
    // ensures: instantiation of this
    // modifes: this

    ~GraphicDisplay();
    // ensures: this no longer exists
    // modifies: this

    void notify() override;
    // ensures: the correct graphics display is shown with the current state of subject
};

#endif