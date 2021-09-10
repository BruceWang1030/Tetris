#include "../../include/blocks/Block.h"
#include <iostream>
using namespace std;

// GETTERS

tuple<int, int> Block::getCoordinates() const
{
    return coordinates_;
}

vector<vector<char>> Block::getCurrRotation()
{
    return rotationTypes_[currentRotation_];
}

int Block::getCurrRotationNumber() const
{
    return currentRotation_;
}

vector<vector<char>> Block::getClockwiseRotation()
{
    int clockwiseRotation = (currentRotation_ + 1) % 4;
    return rotationTypes_[clockwiseRotation];
}

vector<vector<char>> Block::getCounterClockwiseRotation()
{
    int counterClockwiseRotation = currentRotation_ == 0 ? 3 : currentRotation_ - 1;
    return rotationTypes_[counterClockwiseRotation];
}

// SETTERS

void Block::setCoordinates(tuple<int, int> newCoords)
{
    coordinates_ = newCoords;
}

void Block::setCharToHint()
{
    blockChar_ = '?';
}

void Block::setRotation(int rotNum)
{
    currentRotation_ = rotNum % 4;
}

void Block::initializeRotationTypes()
{
    currentRotation_ = 0;
    return;
}

void Block::rotateClockwise()
{
    currentRotation_ = (currentRotation_ + 1) % 4;
}

void Block::rotateCounterClockwise()
{
    currentRotation_ = currentRotation_ == 0 ? 3 : currentRotation_ - 1;
}

int Block::getCreationLevel() const
{
    return creationLevel_;
}

char Block::getBlockChar() const
{
    return blockChar_;
}

ostream &operator<<(ostream &out, Block &block)
{
    for (auto printRow : block.getCurrRotation())
    {
        for (auto printChar : printRow)
            out << printChar;
        out << endl;
    }
    return out;
}
