#include <iostream>
#include <string>
#include <memory>
#include "vector"
#include "../include/GraphicDisplay.h"
#include "../include/Board.h"
#include "../include/Cell.h"
#include "../include/blocks/Block.h"
#include "../include/levels/Level.h"
#include "../include/Scoreboard.h"

using namespace std;

// Constructor
GraphicDisplay::GraphicDisplay(shared_ptr<Gameplay> game) : xDisplay_(Xdisplay(width, height, cellSize))
{
    subject = game;
    xDisplay_.initializeWindow(boardxCoord, boardyCoord, boardWidth, boardHeight);
}

// Destructor
GraphicDisplay::~GraphicDisplay()
{
}

// Helper method to find the differences in the game boards and draw them
void GraphicDisplay::drawBoard(shared_ptr<Board> gameBoard)
{
    int xCoord = 0;
    int yCoord = 0;

    // Draw all the blocks on the game board
    for (auto iter = gameBoard->begin();
         iter != gameBoard->end();
         ++iter)
    {
        Cell cell = *iter;
        shared_ptr<Block> block = cell.getBlock();
        if (!currGameBoard_)
        {
            if (block)
            {
                string colour = blockToColour[block->getBlockChar()];
                xDisplay_.fillCell(xCoord, yCoord, colour);
            }
        }
        else
        {
            if (cell != currGameBoard_->getCell(yCoord, xCoord))
            {
                string colour = (block) ? blockToColour[block->getBlockChar()] : blockToColour[' '];
                xDisplay_.fillCell(xCoord, yCoord, colour);
            }
        }

        xCoord++;
        yCoord += (xCoord / BOARD_NUM_COLS);
        xCoord = xCoord % BOARD_NUM_COLS;
    }
}

// Observer Pattern notify override
void GraphicDisplay::notify()
{
    //Game over
    if (subject->isGameOver())
    {
        if (subject->isShowGameOver())
        {
            xDisplay_.endGame();
        }
        return;
    }

    //clear end game words
    if (subject->getRestarting())
    {
        xDisplay_.clearBoard();
        return;
    }

    // Get all the Game States
    shared_ptr<Board> gameBoard = subject->getBoardState();
    shared_ptr<Scoreboard> scoreboard = subject->getScoreboard();
    shared_ptr<Level> level = subject->getLevel();
    shared_ptr<Block> nextBlock = subject->getNextBlock();

    // Set new level if not current state
    if (currLevel_ != level->getCurrentLevelNumber())
    {
        xDisplay_.writeLevel(to_string(level->getCurrentLevelNumber()));
        currLevel_ = level->getCurrentLevelNumber();
    }

    // Set new score if not current state
    if (currScore_ != scoreboard->getScore())
    {
        xDisplay_.writeScore(to_string(scoreboard->getScore()));
        currScore_ = scoreboard->getScore();
    }

    // Set new high score if not current state
    if (currHighScore_ != scoreboard->getHighScore())
    {
        xDisplay_.writeHighScore(to_string(scoreboard->getHighScore()));
        currHighScore_ = scoreboard->getHighScore();
    }

    // Draw the board
    drawBoard(gameBoard);
    currGameBoard_ = gameBoard;

    // Draw the next
    if (currNextBlock_ != nextBlock)
    {
        string nextColour = blockToColour[nextBlock->getBlockChar()];
        xDisplay_.writeNextBlock(nextBlock->getCurrRotation(), nextColour);
        currNextBlock_ = nextBlock;
    }
}
