#include "../include/Cell.h"
#include <iostream>

using namespace std;

// Getters
shared_ptr<Block> Cell::getBlock() const
{
    return block_;
}

// Setters
void Cell::setBlock(const shared_ptr<Block> block)
{
    block_ = block;
}

// Default Constructor
Cell::Cell() {}

// Copy Constructor
Cell::Cell(const Cell &cell)
{
    block_ = cell.getBlock();
}

// Destructor
Cell::~Cell() {}

// Set the block pointer to nullptr
void Cell::clearBlock()
{
    block_ = nullptr;
}

// Overload << operator to print the block's char it points to
ostream &operator<<(ostream &out, Cell &cell)
{
    if (cell.block_)
        out << cell.block_->getBlockChar();
    else
        out << " ";

    return out;
}

// Overloaded != operator for iterator pattern
bool Cell::operator!=(const Cell &other)
{
    return other.getBlock() != block_;
}