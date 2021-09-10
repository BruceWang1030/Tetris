#include "../include/Board.h"
#include "../include/Cell.h"
#include "../include/Iterator.h"
#include <vector>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <cmath>

using namespace std;

int BOARD_NUM_ROWS = 18;
int BOARD_NUM_COLS = 11;

// Getters
Cell Board::getCell(int row, int col) const
{
    return board_.at(row).at(col);
}

// Setters
void Board::setCell(int row, int col, const std::shared_ptr<Block> block)
{
    board_.at(row).at(col).setBlock(block);
}

// Default Constructor
Board::Board()
{
    vector<Cell> rowCreated;
    for (int rowInd = 0; rowInd < BOARD_NUM_ROWS; rowInd++)
    {
        for (int columnInd = 0; columnInd < BOARD_NUM_COLS; columnInd++)
        {
            rowCreated.emplace_back(Cell());
        }
        board_.emplace_back(rowCreated);
        rowCreated.clear();
    }
}

// Copy Constructor
Board::Board(const Board &board)
{
    vector<Cell> rowCreated;
    for (int rowInd = 0; rowInd < BOARD_NUM_ROWS; rowInd++)
    {
        for (int columnInd = 0; columnInd < BOARD_NUM_COLS; columnInd++)
        {
            Cell cellElem = board.getCell(rowInd, columnInd);
            rowCreated.emplace_back(Cell(cellElem));
        }
        board_.emplace_back(rowCreated);
        rowCreated.clear();
    }
}

// Destructor
Board::~Board() {}

// Iterator Pattern methods
Board::iterator Board::begin()
{
    // Return iterator set at 0 (start of board)
    return Board::iterator(BOARD_NUM_ROWS, BOARD_NUM_COLS, board_, 0, 0);
}

Board::iterator Board::end()
{
    // Return iterator set at size of board (first out of bound position)
    return Board::iterator(BOARD_NUM_ROWS, BOARD_NUM_COLS, board_, BOARD_NUM_ROWS, 0);
}

// iterator Class Methods

// iterator overloaded * operator
Cell &Board::iterator::operator*() const
{
    // returns the char the iterator is at
    return _board.at(_rindex).at(_cindex);
}

// Overloaded << operator to print the each cells in order one at a time
ostream &operator<<(ostream &out, Board &board)
{
    int elCount = 0;
    out << "-----------" << endl;
    for (auto iter = board.begin();
         iter != board.end();
         ++iter)
    {
        elCount++;
        out << *iter;
        if (elCount == BOARD_NUM_COLS)
        {
            out << endl;
            elCount = 0;
        }
    }
    out << "-----------";
    return out;
}

// For hint space finding
int Board::getNextNonEmpty(int row, int col) const
{
    int count = 0;

    while (row < BOARD_NUM_ROWS)
    {
        Cell cell = getCell(row, col);
        if (cell.getBlock())
            break;

        row++;
        count++;
    }

    return count;
}

// Clears all the cells of the board
void Board::clearBoard()
{
    for (auto iter = this->begin();
         iter != this->end();
         ++iter)
    {
        (*iter).clearBlock();
    }
}

// Verifies if a given row (index) is full
bool Board::isRowFull_(const int rowInd)
{
    for (auto cell : board_.at(rowInd))
    {
        if (cell.getBlock() == nullptr)
            return false;
    }
    return true;
}

// Checks the top and bottom rows (if any), if the block is still referenced
bool Board::isBlockCleared_(const int rowInd, const shared_ptr<Block> block)
{
    if (rowInd - 1 > 0)
    {
        for (auto cell : board_.at(rowInd - 1))
        {
            if (block == cell.getBlock())
                return false;
        }
    }

    if (rowInd + 1 < BOARD_NUM_ROWS)
    {
        for (auto cell : board_.at(rowInd + 1))
        {
            if (block == cell.getBlock())
                return false;
        }
    }
    return true;
}

// Calculate the bonus points of a given row (index)
int Board::calculateBonusPoints_(const int rowInd)
{
    int bonusPoints = 0;
    int colInd = 0;
    Cell currCell;
    shared_ptr<Block> currBlock;

    while (colInd < BOARD_NUM_COLS)
    {
        currCell = getCell(rowInd, colInd);
        currBlock = currCell.getBlock();

        if (isBlockCleared_(rowInd, currBlock)){
            bonusPoints += pow(currBlock->getCreationLevel() + 1, 2);
        }

        while (colInd + 1 < BOARD_NUM_COLS && getCell(rowInd, colInd + 1).getBlock() == currBlock)
            colInd++;

        colInd++;
    }
    return bonusPoints;
}

// Clearing rows if complete
pair<int, int> Board::clearRows()
{
    int rowClearedCount = 0;
    int bonusPoints = 0;

    vector<Cell> newRow;
    for (int columnInd = 0; columnInd < BOARD_NUM_COLS; columnInd++)
        newRow.emplace_back(Cell());

    for (int rowInd = 0; rowInd < BOARD_NUM_ROWS; rowInd++)
    {
        if (isRowFull_(rowInd))
        {
            rowClearedCount++;
            bonusPoints += calculateBonusPoints_(rowInd);
            board_.erase(board_.begin() + rowInd);
            board_.insert(board_.begin(), newRow);
        }
    }
    pair<int, int> out(rowClearedCount, bonusPoints);
    return out;
}
