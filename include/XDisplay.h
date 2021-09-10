#ifndef _XDISPLAY_H_
#define _XDISPLAY_H_
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <map>

class Xdisplay
{

    // X11/Xlib environment
    Display *display_;
    Window window_;
    GC graphicContext_;

    // Pixel colour from colour name to pixel
    std::map<std::string, int> colourMap_;

    // Window information
    int width_;
    int height_;
    int screen_;

    // Text information
    Font font_;
    XTextItem textIt_;

    // Board details
    int cellSize_;
    int boardxCoord_;
    int boardyCoord_;
    int boardWidth_;
    int boardHeight_;

public:
    Xdisplay(int width, int height, int cellSize);
    // takes: the window width and height, the cell size in the board
    // ensures: Instantiation of this, initialization of X11/Xlib environment, window information, text information and colour map
    // modifies: this

    ~Xdisplay();
    // ensures: this no longer exists
    // modifies: this

    void initializeWindow(int x, int y, int boardWidth, int boardHeight);
    // takes: the x and y coordinates of the board's top left corner, the board width and height
    // ensures: the information text, and the board are drawn on the window
    // modifies: display_, board's x,y coordinates, width and height

    void fillCell(int x, int y, std::string colour);
    // takes: the x and y coordinates of the cell in the board, and the colour of the cell
    // ensures: the cell (of cell size x cell size) is coloured in the given parameter
    // modifies: display_

    void clearBoard();
    // ensures: the body of the board is empty (filled in white)
    // modifies: display_

    void writeLevel(std::string level);
    // takes: the new level string
    // ensures: the current level is overwritten with the given level
    // modifies: display_

    void writeScore(std::string score);
    // takes: the new score string
    // ensures: the current score is overwritten with the given score
    // modifies: display_

    void writeHighScore(std::string HighScore);
    // takes: the new high score string
    // ensures: the current high score is overwritten with the given high score
    // modifies: display_

    void writeNextBlock(std::vector<std::vector<char>> blockVector, std::string colour = "black");
    // takes: the current block rotation, and the colour to be drawn with
    // ensures: the current block rotation is drawn using the given colour under the text "Next:"
    // modifies: display_

    void endGame();
    //ensures: game is over is printed on the window
    // modifies: display_
};

#endif