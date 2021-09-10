#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <assert.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include "../include/XDisplay.h"

using namespace std;

// Constructor
Xdisplay::Xdisplay(int width, int height, int cellSize) : width_(width), height_(height), cellSize_(cellSize)
{

    // Creating display + window
    display_ = XOpenDisplay(NULL);
    assert(display_);
    screen_ = DefaultScreen(display_);

    colourMap_["black"] = BlackPixel(display_, screen_);
    colourMap_["white"] = WhitePixel(display_, screen_);

    window_ = XCreateSimpleWindow(display_, RootWindow(display_, screen_), 0, 0, width_, height_, 0,
                                  colourMap_["black"], colourMap_["white"]);

    // Display configurations
    XSelectInput(display_, window_, ExposureMask);
    XMapRaised(display_, window_);

    Pixmap pix = XCreatePixmap(display_, window_, width_, height_, DefaultDepth(display_, screen_));
    graphicContext_ = XCreateGC(display_, pix, 0, nullptr);

    XFlush(display_);
    XFlush(display_);

    // Set up colours Map
    XColor xcolour;
    vector<char const *> colorVals = {"red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};
    Colormap cMap = DefaultColormap(display_, screen_);

    for (auto colour : colorVals)
    {
        if (!XParseColor(display_, cMap, colour, &xcolour))
        {
            cerr << "Bad colour: " << colour << endl;
        }
        if (!XAllocColor(display_, cMap, &xcolour))
        {
            cerr << "Bad colour: " << colour << endl;
        }
        colourMap_[colour] = xcolour.pixel;
    }

    XSetForeground(display_, graphicContext_, colourMap_["black"]);

    // Make window non-resizeable
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize);

    hints.height = hints.base_height = hints.min_height = hints.max_height = height_;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width_;

    XSetNormalHints(display_, window_, &hints);
    XSynchronize(display_, True);

    font_ = XLoadFont(display_, "6x13");
    textIt_.delta = 0;
    textIt_.font = font_;

    usleep(1000);
}

// Draw the skeleton of the window
void Xdisplay::initializeWindow(int x, int y, int boardWidth, int boardHeight)
{
    boardxCoord_ = x;
    boardyCoord_ = y;
    boardWidth_ = boardWidth;
    boardHeight_ = boardHeight;

    string title = "QUADRIS";
    textIt_.chars = const_cast<char *>(title.c_str());
    textIt_.nchars = title.length();

    textIt_.font = XLoadFont(display_, "-*-helvetica-bold-r-normal--*-120-*-*-*-*-*");
    XDrawText(display_, window_, graphicContext_, 75, 20, &textIt_, 1);
    textIt_.font = XLoadFont(display_, "6x13");

    XDrawRectangle(display_, window_, graphicContext_, boardxCoord_ - 1, boardyCoord_ - 1, boardWidth_ + 1, boardHeight_ + 1);

    int offset = 60;
    vector<string> topInfo = {"Level:", "Score:", "High Score:", "Next:"};

    // Draw all the information text
    for (auto msg : topInfo)
    {
        textIt_.chars = const_cast<char *>(msg.c_str());
        textIt_.nchars = msg.length();

        if (msg == "Next:")
            XDrawText(display_, window_, graphicContext_, x, y + boardHeight + 30, &textIt_, 1);
        else
        {
            XDrawText(display_, window_, graphicContext_, x, y - offset, &textIt_, 1);
            offset -= 20;
        }
    }

    XFlush(display_);
}

// Destructor
Xdisplay::~Xdisplay()
{

    // Free Graphics and close display
    XFreeGC(display_, graphicContext_);
    XCloseDisplay(display_);
}

// fill a cell with a given colour
void Xdisplay::fillCell(int x, int y, std::string colour)
{
    int xCoordStart = boardxCoord_ + cellSize_ * x;
    int yCoordStart = boardyCoord_ + cellSize_ * y;

    XSetForeground(display_, graphicContext_, colourMap_[colour]);
    XFillRectangle(display_, window_, graphicContext_, xCoordStart + 1, yCoordStart + 1, cellSize_ - 1, cellSize_ - 1);
    XSetForeground(display_, graphicContext_, colourMap_["black"]);

    XFlush(display_);
}

// fill a white rectangle over board
void Xdisplay::clearBoard()
{
    XSetForeground(display_, graphicContext_, colourMap_["white"]);
    XFillRectangle(display_, window_, graphicContext_, boardxCoord_, boardyCoord_, boardWidth_, boardHeight_);
    XFlush(display_);
}

// overwrite current level
void Xdisplay::writeLevel(string level)
{
    textIt_.chars = const_cast<char *>(level.c_str());
    textIt_.nchars = level.length();

    XSetForeground(display_, graphicContext_, colourMap_["white"]);
    XFillRectangle(display_, window_, graphicContext_, boardxCoord_ + 150, boardyCoord_ - 70, 25, 10);
    XSetForeground(display_, graphicContext_, colourMap_["black"]);

    XDrawText(display_, window_, graphicContext_, boardxCoord_ + 150, boardyCoord_ - 60, &textIt_, 1);
    XFlush(display_);
}

// overwrite current score
void Xdisplay::writeScore(string score)
{

    textIt_.chars = const_cast<char *>(score.c_str());
    textIt_.nchars = score.length();

    XSetForeground(display_, graphicContext_, colourMap_["white"]);
    XFillRectangle(display_, window_, graphicContext_, boardxCoord_ + 150, boardyCoord_ - 50, 25, 10);
    XSetForeground(display_, graphicContext_, colourMap_["black"]);

    XDrawText(display_, window_, graphicContext_, boardxCoord_ + 150, boardyCoord_ - 40, &textIt_, 1);
    XFlush(display_);
}

// overwrite current highscore
void Xdisplay::writeHighScore(string HighScore)
{
    textIt_.chars = const_cast<char *>(HighScore.c_str());
    textIt_.nchars = HighScore.length();

    XSetForeground(display_, graphicContext_, colourMap_["white"]);
    XFillRectangle(display_, window_, graphicContext_, boardxCoord_ + 150, boardyCoord_ - 30, 25, 10);
    XSetForeground(display_, graphicContext_, colourMap_["black"]);

    XDrawText(display_, window_, graphicContext_, boardxCoord_ + 150, boardyCoord_ - 20, &textIt_, 1);
    XFlush(display_);
}

// overwrite next block display
void Xdisplay::writeNextBlock(vector<vector<char>> blockVector, string colour)
{
    int xNextLoc = boardxCoord_;
    int yNextLoc = boardyCoord_ + boardHeight_ + 40;

    // Hide previous block
    XSetForeground(display_, graphicContext_, colourMap_["white"]);
    XFillRectangle(display_, window_, graphicContext_, xNextLoc, yNextLoc, cellSize_ * 4, cellSize_ * 4);
    XFlush(display_);

    XSetForeground(display_, graphicContext_, colourMap_[colour]);

    // Draw current block
    for (auto row : blockVector)
    {
        for (auto blockChar : row)
        {
            if (blockChar != ' ')
            {
                XFillRectangle(display_, window_, graphicContext_, xNextLoc + 1, yNextLoc + 1, cellSize_ - 1, cellSize_ - 1);
            }
            xNextLoc += cellSize_;
        }
        xNextLoc = boardxCoord_;
        yNextLoc += cellSize_;
    }

    XSetForeground(display_, graphicContext_, colourMap_["black"]);
    XFlush(display_);
}

// Draw endGame message on the display
void Xdisplay::endGame()
{
    // Draw background of message
    XSetForeground(display_, graphicContext_, colourMap_["white"]);
    XFillRectangle(display_, window_, graphicContext_, width_ / 4 + 20, height_ / 2 - 20, 70, 60);
    XSetForeground(display_, graphicContext_, colourMap_["black"]);

    // Write Game Over
    string gameOver = "Game Over";
    textIt_.chars = const_cast<char *>(gameOver.c_str());
    textIt_.nchars = gameOver.length();
    XDrawText(display_, window_, graphicContext_, width_ / 4 + 25, height_ / 2, &textIt_, 1);

    // Write Try Again?
    string tryAgain = "Try Again?";
    textIt_.chars = const_cast<char *>(tryAgain.c_str());
    textIt_.nchars = tryAgain.length();
    XDrawText(display_, window_, graphicContext_, width_ / 4 + 25, height_ / 2 + 25, &textIt_, 1);

    XFlush(display_);
}