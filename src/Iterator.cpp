#include "../include/Iterator.h"
#include "../include/Board.h"
using namespace std;

// Overload ++ operator for Iterator template
BoardIterator &BoardIterator::operator++()
{
  // Incrementing the indices of column;
  // if we have reached the end -> _cindex becomes 0 and _rindex is incremented by 1
  _cindex++;
  _rindex = _cindex / _colsize + _rindex;
  _cindex = _cindex % _colsize;

  return *this;
}

// Overload != operator for Iterator template
bool BoardIterator::operator!=(const BoardIterator &other)
{
  // Check if board is different or one of the indices is different => true
  return _board.data() != other._board.data() || _rindex != other._rindex || _cindex != other._cindex;
}