#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <memory>
#include <utility>
#include "Cell.h"
#include "Iterator.h"
#include "blocks/Block.h"


extern int BOARD_NUM_ROWS;
extern int BOARD_NUM_COLS;

class Board
{

  // Specification fields:
	// board_ = a 2D vector of Cell Object which represents the game board itself

    std::vector<std::vector<Cell>> board_;

    // Returns if the row is complete
    bool isRowFull_(const int rowInd);
    // Checks if a block is still referenced in the board
    bool isBlockCleared_(const int rowInd, const std::shared_ptr<Block> block);
    // Calculates the bonus points of a given cleared row
    int calculateBonusPoints_(const int rowInd);

public: 
    Board();
    // modifies: this
	  // ensures: instantiation of this

    virtual ~Board();
    // modifies: this
    // ensures: this no longer exists

    // Copy Constructor
		Board(const Board &board); //lvalue reference: &

    Cell getCell(int row, int col) const;
    // takes: a row index and a col index
    // ensures: nothing is changed
    // returns: the Cell at the given location

    int getNextNonEmpty(int row, int col) const;
    // takes: a row index and a col index
    // ensures: nothing is changed
    // returns: the hole size below a given coordinate

    void setCell(int row, int col, const std::shared_ptr<Block> block);
    // takes: a row index and a col index, and a block pointer
    // ensures: the block_ field of the cell at the coordinates is set to the block ptr
    
    std::pair<int,int> clearRows();
    // ensures: The lines that are complete are cleared and the board still has 18 rows
    // returns: pair where the pair.first is the number of lines cleared and pair.second is the bonus points
    
    void clearBoard();
    // ensures: All the cells of the board points to null

    // iterator class
    class iterator;

    iterator begin();
    // ensures: 0 is the index on the created iterator
    // returns: iterator set at beginning of board

    iterator end();
    // ensures: size is the index on the created iterator
    // returns: iterator set at end of board

    friend std::ostream &operator<<(std::ostream &, Board &);
};


// Iterator class definition
class Board::iterator : public BoardIterator
{
public:
  iterator(int rowsize, int colsize, std::vector<std::vector<Cell>> &board, int rindex, int cindex) : 
  BoardIterator(rowsize, colsize, board, rindex, cindex) {}
  // modifies: this
  // requires: row size and colsize of iterated elements, pointer to the board, a current row and column index
  // ensures: instantiation of this + all paramenters of inherited iterator are given

  Cell &operator*() const;
  // ensures: nothing is modified in the process
  // returns: reference to the char the iterator points to
};

#endif