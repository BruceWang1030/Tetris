#include "../../include/blocks/IBlock.h"

IBlock::IBlock()
{
    coordinates_ = {0, 3};
    rotationTypes_ = {
        {{'I', 'I', 'I', 'I'}},
        {{'I'},
         {'I'},
         {'I'},
         {'I'}},
        {{'I', 'I', 'I', 'I'}},
        {{'I'},
         {'I'},
         {'I'},
         {'I'}}};

    currentRotation_ = 0;
    creationLevel_ = 0; //To-Do: modify after adding level
    blockChar_ = 'I';
}
