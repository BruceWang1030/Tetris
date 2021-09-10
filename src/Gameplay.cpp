#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <cmath>
#include "../include/Gameplay.h"
#include "../include/HintGenerator.h"
#include "../include/BlockFactory.h"
#include "../include/LevelFactory.h"
#include "../include/Cell.h"
#include "../include/levels/Level.h"
#include "../include/levels/Level0.h"
#include "../include/levels/Level1.h"
#include "../include/levels/Level2.h"
#include "../include/levels/Level3.h"
#include "../include/levels/Level4.h"
using namespace std;

// Constructor
Gameplay::Gameplay(string blockSequenceFile, int startLevel)
{
    gameInfo_ = shared_ptr<GameInfo>(new GameInfo());
    setBoard(shared_ptr<Board>(new Board()));
    setScoreboard(shared_ptr<Scoreboard>(new Scoreboard()));
    setHintGen(shared_ptr<HintGenerator>(new HintGenerator()));
    setBlockSequenceFile(blockSequenceFile);
    setLevel(startLevel);

    shared_ptr<Level> currLevel = getLevel();
    currLevel->useBlockSequenceFile(blockSequenceFile);

    setCurrBlock(currLevel->generateNextBlock());
    setNextBlock(currLevel->generateNextBlock());

    // Start without AI Mode
    setAIMode(false);
}

// GETTERS

shared_ptr<Block> Gameplay::getCurrBlock() const
{
    return gameInfo_->currBlock_;
}

shared_ptr<Block> Gameplay::getNextBlock() const
{
    return gameInfo_->nextBlock_;
}

shared_ptr<Block> Gameplay::getHintBlock() const
{
    return gameInfo_->hintBlock_;
}

shared_ptr<Board> Gameplay::getBoard() const
{
    return gameInfo_->board_;
}

shared_ptr<Scoreboard> Gameplay::getScoreboard() const
{
    return gameInfo_->scoreboard_;
}

shared_ptr<HintGenerator> Gameplay::getHintGen() const
{
    return gameInfo_->hintGen_;
}

shared_ptr<Board> Gameplay::getBoardState() const
{
    // get the current board
    shared_ptr<Board> currBoard = getBoard();

    // create a temp board
    shared_ptr<Board> tempBoard(new Board(*currBoard));
    addBlockToBoard(getCurrBlock(), tempBoard);

    shared_ptr<Block> hintBlock = getHintBlock();
    if (hintBlock)
        addBlockToBoard(hintBlock, tempBoard);

    return tempBoard;
}

int Gameplay::getStartLevel() const
{
    return gameInfo_->startLevel_;
}

string Gameplay::getBlockSequenceFile() const
{
    return gameInfo_->blockSequenceFile_;
}

string Gameplay::getCommandSequenceFile() const
{
    return gameInfo_->commandSequenceFile_;
}

shared_ptr<Level> Gameplay::getLevel() const
{
    return gameInfo_->currLevel_;
}

bool Gameplay::getRestarting() const
{
    return gameInfo_->isRestarting_;
}
bool Gameplay::isAIMode() const
{
    return gameInfo_->isAIMode_;
}
bool Gameplay::isShowGameOver() const
{
    return gameInfo_->isShowingGameOver;
}

// SETTERS
void Gameplay::setCurrBlock(shared_ptr<Block> newBlock)
{
    gameInfo_->currBlock_ = newBlock;
}

void Gameplay::setNextBlock(shared_ptr<Block> newBlock)
{
    gameInfo_->nextBlock_ = newBlock;
}

void Gameplay::setHintBlock(shared_ptr<Block> newBlock)
{
    gameInfo_->hintBlock_ = newBlock;
}

void Gameplay::setBoard(shared_ptr<Board> newBoard)
{
    gameInfo_->board_ = newBoard;
}

void Gameplay::setScoreboard(shared_ptr<Scoreboard> newScoreboard)
{
    gameInfo_->scoreboard_ = newScoreboard;
}

void Gameplay::setHintGen(shared_ptr<HintGenerator> hintGen)
{
    gameInfo_->hintGen_ = hintGen;
}

void Gameplay::setStartLevel(int startLevel)
{
    gameInfo_->startLevel_ = startLevel;
}

void Gameplay::setBlockSequenceFile(std::string file)
{
    gameInfo_->blockSequenceFile_ = file;
}
void Gameplay::setAIMode(bool AIMode)
{
    // Check if level 3 or 4
    shared_ptr<Level> currLevel = getLevel();
    int levelNumber = currLevel->getCurrentLevelNumber();
    if (levelNumber == 3 || levelNumber == 4)
    {
        cout << "AI Mode cannot be enabled in levels 3 and 4. I'm still learning..." << endl;
        return;
    }
    gameInfo_->isAIMode_ = AIMode;
}

void Gameplay::setCommandSequenceFile(std::string file)
{
    gameInfo_->commandSequenceFile_ = file;
}

void Gameplay::setLevel(int level)
{
    shared_ptr<Level> newLevel = LevelFactory::createLevel("Level" + to_string(level));
    gameInfo_->currLevel_ = newLevel;
}

void Gameplay::setRestarting(bool isRestarting)
{
    gameInfo_->isRestarting_ = isRestarting;
}

void Gameplay::setShowGameOver(bool showGameOver)
{
    gameInfo_->isShowingGameOver = showGameOver;
}

void Gameplay::startTurn()
{
    notifyObservers();
}

void Gameplay::updateScore(bool isDropCmd)
{
    shared_ptr<Board> board = getBoard();
    tuple<int, int> clearResult = board->clearRows();
    int numRowsCleared = get<0>(clearResult);
    int bonusPoints = get<1>(clearResult);
    addToScore(bonusPoints);

    //calculate new scores
    if (numRowsCleared > 0)
    {
        int scorePoints = getLevel()->calculateNewPoints(numRowsCleared);
        addToScore(scorePoints);
    }

    //brownBlockForLevel4 is always a nullptr if it's not level4
    if (isDropCmd)
    {
        shared_ptr<Block> brownBlockForLevel4 = getLevel()->handleAfterRowClear(numRowsCleared > 0);
        if (brownBlockForLevel4 != nullptr)
        {
            //TO-DO: place it in the center of board and drop
            dropBrownBlockToBoard(brownBlockForLevel4);

            //clearrows
            clearResult = board->clearRows();
            numRowsCleared = get<0>(clearResult);
            bonusPoints = get<1>(clearResult);
            addToScore(bonusPoints);

            //claculate new scores
            if (numRowsCleared > 0)
            {
                int scorePoints = getLevel()->calculateNewPoints(numRowsCleared);
                addToScore(scorePoints);
            }
        }
    }
}

bool Gameplay::isGameOver()
{
    // get the current block rotation and coordinates
    shared_ptr<Block> currBlock = getCurrBlock();
    vector<vector<char>> currRotation = currBlock->getCurrRotation();
    tuple<int, int> coords = currBlock->getCoordinates();
    int x = get<0>(coords);
    int y = get<1>(coords);
    if (hasCollision(x, y, currRotation))
    {
        return true;
    }
    return false;
}

vector<shared_ptr<Command>> Gameplay::modifyCommands(vector<vector<shared_ptr<Command>>> commands)
{
    // Modify Commands based on level
    getLevel()->modifyCommands(commands);
    // Flatten 2D vector of commands
    vector<shared_ptr<Command>> flattened;
    for (auto cmdSeq : commands)
    {
        for (auto command : cmdSeq)
        {
            flattened.push_back(command);
        }
    }
    return flattened;
}

/* Block Generation */
void Gameplay::generateBlock(string blockType)
{
    // Replace currBlock with the new block
    shared_ptr<Block> newBlock = BlockFactory::createBlock(blockType + "Block");
    setCurrBlock(newBlock);
}

/* Moves */
bool Gameplay::moveLeft(std::shared_ptr<Block> block)
{
    // shared_ptr<Block> currBlock = getCurrBlock();
    tuple<int, int> currCoords = block->getCoordinates();

    // X and Y correspond to bottom-left cell in block
    int x = get<0>(currCoords);
    int y = get<1>(currCoords);

    vector<vector<char>> currRotation = block->getCurrRotation();

    // Check for collisions
    if (hasCollision(x - 1, y, currRotation))
        return false;

    // There was no collision, so set the new coordinates
    get<0>(currCoords) = x - 1;
    block->setCoordinates(currCoords);
    return true;
}

bool Gameplay::moveRight(std::shared_ptr<Block> block)
{
    // shared_ptr<Block> currBlock = getCurrBlock();
    tuple<int, int> currCoords = block->getCoordinates();

    // X and Y correspond to bottom-left cell in block
    int x = get<0>(currCoords);
    int y = get<1>(currCoords);

    vector<vector<char>> currRotation = block->getCurrRotation();

    // Check for collisions
    if (hasCollision(x + 1, y, currRotation))
        return false;

    // There was no collision, so set the new coordinates
    get<0>(currCoords) = x + 1;
    block->setCoordinates(currCoords);
    return true;
}

bool Gameplay::moveDown(std::shared_ptr<Block> block)
{
    // shared_ptr<Block> currBlock = getCurrBlock();
    tuple<int, int> currCoords = block->getCoordinates();

    // X and Y correspond to bottom-left cell in block
    int x = get<0>(currCoords);
    int y = get<1>(currCoords);

    vector<vector<char>> currRotation = block->getCurrRotation();

    // Check for collisions
    if (hasCollision(x, y + 1, currRotation))
        return false;

    // There was no collision, so set the new coordinates
    get<1>(currCoords) = y + 1;
    block->setCoordinates(currCoords);
    return true;
}

void Gameplay::dropBlock()
{
    bool canMoveDown = true;
    while (canMoveDown)
    {
        canMoveDown = moveDown(getCurrBlock());
    }

    // Add currBlock to board
    addBlockToBoard(getCurrBlock(), getBoard());

    // swap currBlock with nextBlock
    shared_ptr<Block> nextBlock = getNextBlock();
    setCurrBlock(nextBlock);
    // generate new nextBlock
    shared_ptr<Level> currLevel = getLevel();
    shared_ptr<Block> newNext = currLevel->generateNextBlock();
    setNextBlock(newNext);
}

void Gameplay::dropBrownBlockToBoard(shared_ptr<Block> bblk)
{
    bool canMoveDown = true;
    while (canMoveDown)
    {
        tuple<int, int> currCoords = bblk->getCoordinates();

        // X and Y correspond to bottom-left cell in block
        int x = get<0>(currCoords);
        int y = get<1>(currCoords);

        vector<vector<char>> currRotation = bblk->getCurrRotation();

        // Check for collisions
        if (hasCollision(x, y + 1, currRotation))
            break;

        // There was no collision, so set the new coordinates
        get<1>(currCoords) = y + 1;
        bblk->setCoordinates(currCoords);
        canMoveDown = true;
    }

    // Add currBlock to board
    tuple<int, int> currCoords = bblk->getCoordinates();

    // X and Y correspond to bottom-left cell in block
    int x = get<0>(currCoords);
    int y = get<1>(currCoords);

    vector<vector<char>> currRotation = bblk->getCurrRotation();

    shared_ptr<Board> board = getBoard();

    // add block to board
    int numRotationRows = currRotation.size();
    for (int row = 0; row < currRotation.size(); row++)
    {
        vector<char> currRow = currRotation[row];
        for (int col = 0; col < currRow.size(); col++)
        {
            if (currRow[col] == ' ')
                continue;
            int xCoord = x + col;
            int yCoord = y - (numRotationRows - 1 - row);
            // Set tempBoard val at xCoord, yCoord to currBlockkj
            board->setCell(yCoord, xCoord, bblk);
        }
    }
    return;
}

/* Rotations */
void Gameplay::rotateClockwise()
{
    shared_ptr<Block> currBlock = getCurrBlock();
    tuple<int, int> currCoords = currBlock->getCoordinates();
    // X and Y correspond to bottom-left cell in block
    int x = get<0>(currCoords);
    int y = get<1>(currCoords);

    vector<vector<char>> potentialRotation = currBlock->getClockwiseRotation();

    // Check for collision on potentialRotation
    if (hasCollision(x, y, potentialRotation))
        return;

    // No collision, so rotate the currBlock
    currBlock->rotateClockwise();
}

void Gameplay::rotateCounterClockwise()
{
    shared_ptr<Block> currBlock = getCurrBlock();
    tuple<int, int> currCoords = currBlock->getCoordinates();
    // X and Y correspond to bottom-left cell in block
    int x = get<0>(currCoords);
    int y = get<1>(currCoords);

    vector<vector<char>> potentialRotation = currBlock->getCounterClockwiseRotation();

    // Check for collision on potentialRotation
    if (hasCollision(x, y, potentialRotation))
        return;

    // No collision, so rotate the currBlock
    currBlock->rotateCounterClockwise();
}

/* Level */
void Gameplay::levelUp()
{
    int currLevelNumber = getLevel()->getCurrentLevelNumber();
    if (currLevelNumber == 4)
        return;

    int nextLevelNumber = currLevelNumber + 1;
    setLevel(nextLevelNumber);
}

void Gameplay::levelDown()
{
    int currLevelNumber = getLevel()->getCurrentLevelNumber();
    if (currLevelNumber == 0)
        return;

    int nextLevelNumber = currLevelNumber - 1;
    setLevel(nextLevelNumber);
    shared_ptr<Level> currLevel = getLevel();
    string blockSequenceFile = getBlockSequenceFile();
    currLevel->useBlockSequenceFile(blockSequenceFile);
}

void Gameplay::noRandom(string fileName)
{
    shared_ptr<Level> currLevel = getLevel();

    // Set level to noRandom
    currLevel->setIsRandom(false);

    // Set the file in the levela
    currLevel->useNoRandomFile(fileName);
}

void Gameplay::random()
{
    shared_ptr<Level> currLevel = getLevel();

    // Set level to random
    currLevel->setIsRandom(true);
}

void Gameplay::restart()
{
    setRestarting(true);
    // Reset the board
    getBoard()->clearBoard();

    // Reset the score
    getScoreboard()->setScore(0);

    // Reset level
    int startLevel = getStartLevel();
    setLevel(startLevel);

    // Set the blockSequenceFile
    shared_ptr<Level> currLevel = getLevel();
    string blockSequenceFile = getBlockSequenceFile();
    currLevel->useBlockSequenceFile(blockSequenceFile);

    // Reset currBlock and nextBlock
    setCurrBlock(currLevel->generateNextBlock());
    setNextBlock(currLevel->generateNextBlock());

    notifyObservers();
    setRestarting(false);
}

void Gameplay::useSequence()
{
}

void Gameplay::generateHint()
{
    shared_ptr<HintGenerator> hintGen = getHintGen();
    hintGen->generateHint(this);
}

/* HELPERS */

bool Gameplay::hasCollision(int x, int y, vector<vector<char>> currRotation)
{

    // Check if there is a collision with wall or other block on board
    int numRotationRows = currRotation.size();
    for (int row = 0; row < currRotation.size(); row++)
    {
        vector<char> currRow = currRotation[row];
        // Look through cells in the given row and check if empty
        for (int col = 0; col < currRow.size(); col++)
        {
            if (currRow[col] != ' ')
            {
                // there is part of a block in this row
                int boardX = x + col;
                int boardY = y - (numRotationRows - 1 - row);

                // Hit wall on left
                if (boardX < 0)
                    return true;
                // Hit wall on right
                if (boardX >= BOARD_NUM_COLS)
                    return true;
                // Hit Bottom
                if (boardY >= BOARD_NUM_ROWS)
                    return true;

                // Check if the cell below in the board is empty
                shared_ptr<Board> board = getBoard();
                Cell cell = board->getCell(boardY, boardX);
                if (nullptr != cell.getBlock())
                    return true;
            }
        }
    }
    return false;
}

void Gameplay::addBlockToBoard(shared_ptr<Block> block, shared_ptr<Board> board) const
{
    tuple<int, int> currCoords = block->getCoordinates();

    // X and Y correspond to bottom-left cell in block
    int x = get<0>(currCoords);
    int y = get<1>(currCoords);
    vector<vector<char>> currRotation = block->getCurrRotation();

    // add block to board
    int numRotationRows = currRotation.size();
    for (int row = 0; row < currRotation.size(); row++)
    {
        vector<char> currRow = currRotation[row];
        for (int col = 0; col < currRow.size(); col++)
        {
            if (currRow[col] == ' ')
                continue;
            int xCoord = x + col;
            int yCoord = y - (numRotationRows - 1 - row);
            // Set tempBoard val at xCoord, yCoord to currBlockkj
            board->setCell(yCoord, xCoord, block);
        }
    }
}

void Gameplay::addToScore(int pointsToAdd)
{
    int currScore = gameInfo_->scoreboard_->getScore();
    gameInfo_->scoreboard_->setScore(currScore + pointsToAdd);
}

void Gameplay::playTurnAI()
{
    // Set a Hint Block
    generateHint();

    // Get the current and hint Blocks
    shared_ptr<Block> currBlock = getCurrBlock();
    shared_ptr<Block> hintBlock = getHintBlock();

    // Set the current Block's position to the hint Block's location
    currBlock->setCoordinates(hintBlock->getCoordinates());

    // Set the current Block's rotation to the hint Block's rotation
    currBlock->setRotation(hintBlock->getCurrRotationNumber());

    // Drop the current block at the Hint's location
    dropBlock();
    setHintBlock(nullptr);
}
