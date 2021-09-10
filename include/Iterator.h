#ifndef ITERS_H
#define ITERS_H

#include <vector>
#include <iostream>
#include "Cell.h"

class BoardIterator
{
	// Specification fields:

	// _rowsize = row size of the iterated subject
	// _colsize = col size of the iterated subject
	// _board = pointer to the board (data)
	// _rindex = current row index of the iteration
	// _cindex = current column index of the iteration

public:
	BoardIterator(int rowsize, int colsize, std::vector<std::vector<Cell>> &board, int rindex, int cindex) : _rowsize{rowsize},
		 _colsize{colsize}, _board{board}, _rindex{rindex}, _cindex{cindex} {}
	// modifies: this
	// requires: row size and colsize of iterated elements, pointer to the board, a current row and column index
	// ensures: instantiation of this + all fields are assigned by their given arguments

	BoardIterator &operator++();
	// modifies: _rindex and/or _cindex
	// ensures: overloaded + operator, we have incremented the iterator indices by 1
	// returns: this (with increment done)

	bool operator!=(const BoardIterator &other);
	// requires: other BoardIterator to be compared with
	// ensures: overloaded != operator, nothing is modified in the process
	// returns: true if the iterator are pointing to the same data and indices

	friend class Board;

protected:
	// fields
	int _rowsize;
	int _colsize;
	std::vector<std::vector<Cell>> &_board;
	int _rindex;
	int _cindex;
};

#endif