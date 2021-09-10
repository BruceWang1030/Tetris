#include "../../include/blocks/BBlock.h"

BBlock::BBlock()
{
    coordinates_ = {5, 3};
    rotationTypes_ = {
        {{'*'}},
        {{'*'}},
        {{'*'}},
        {{'*'}}};

    currentRotation_ = 0;
    creationLevel_ = 0; //To-Do: modify after adding level
    blockChar_ = '*';
}