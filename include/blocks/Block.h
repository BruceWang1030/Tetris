#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <tuple>
#include <vector>
#include <memory>

class Block : public std::enable_shared_from_this<Block>
{
protected:
    //the coordinates_ records the bottom left corner of the block (might be empty block)
    std::tuple<int, int> coordinates_;

    //4 rotationTypes: (indexed by curentRotation)
    std::vector<std::vector<std::vector<char>>> rotationTypes_;

    //0: initial; 1: right 90 degree; 2: 180 degree; 3: left 90 degree
    int currentRotation_;

    //To-do need to add ways to modify the creationLevel_ from level side
    int creationLevel_;

    char blockChar_;

    //This function sets the currentRotaion_ to 0
    virtual void initializeRotationTypes();

public:

    virtual ~Block(){};

    // Rotations
    void rotateClockwise();
    void rotateCounterClockwise();

    //get the letter denotated for type of block: I, O, L, J ......
    // virtual char getBlockChar() = 0;

    // GETTERS
    std::tuple<int, int> getCoordinates() const;
    std::vector<std::vector<char>> getCurrRotation();
    std::vector<std::vector<char>> getClockwiseRotation();
    std::vector<std::vector<char>> getCounterClockwiseRotation();

    int getCreationLevel() const;
    char getBlockChar() const;
    int getCurrRotationNumber() const;

    // SETTERS
    void setCoordinates(std::tuple<int, int>);
    void setCharToHint();
    void setRotation(int);

    friend std::ostream &operator<<(std::ostream &, Block &);
};

#endif
