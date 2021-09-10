#ifndef CELL_H_
#define CELL_H_

#include <memory>
#include "./blocks/Block.h"

class Block;

class Cell
{
    // Specification fields:
	// block_ = Block pointer to the block_ the cell holds

    std::shared_ptr<Block> block_;

public:
    Cell();
    // modifies: this
    // ensures: instantiation of this

    // Copy constructor
    Cell(const Cell &cell);

    virtual ~Cell();
    // modifies: this
    // ensures: this no longer exists

    void clearBlock();
    // modifies: block_
    // ensures: block_ is set to nullptr

    std::shared_ptr<Block> getBlock() const;
    // returns: block_

    void setBlock(const std::shared_ptr<Block>);
    // takes: a Block pointer
    // ensures: block_ is set to the given Block pointer
    // modifies: block_
    
    bool operator!=(const Cell &other);
    // takes: reference to other Cell object
    // returns: if the Block pointers are equal
    
    friend std::ostream &operator<<(std::ostream &, Cell &);
    // takes: reference to ostream object, and cell object
    // ensures: the block Char of the block_ has been passed to the ostream obj
};

#endif
