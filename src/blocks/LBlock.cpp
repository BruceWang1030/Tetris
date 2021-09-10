#include "../../include/blocks/LBlock.h"

LBlock::LBlock()
{
    coordinates_ = {0, 4};
    rotationTypes_ = {
        {{' ', ' ', 'L'},
         {'L', 'L', 'L'}},
        {{'L'},
         {'L'},
         {'L', 'L'}},
        {{'L', 'L', 'L'},
         {'L'}},
        {{'L', 'L'},
         {' ', 'L'},
         {' ', 'L'}}};

    currentRotation_ = 0;
    creationLevel_ = 0; //To-Do: modify after adding level
    blockChar_ = 'L';
}
