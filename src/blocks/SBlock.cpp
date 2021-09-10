#include "../../include/blocks/SBlock.h"

SBlock::SBlock()
{
    coordinates_ = {0, 4};
    rotationTypes_ = {
        {{' ', 'S', 'S'},
         {'S', 'S', ' '}},
        {{'S', ' '},
         {'S', 'S'},
         {' ', 'S'}},
        {{' ', 'S', 'S'},
         {'S', 'S', ' '}},
        {{'S', ' '},
         {'S', 'S'},
         {' ', 'S'}}};

    currentRotation_ = 0;
    creationLevel_ = 0; //To-Do: modify after adding level
    blockChar_ = 'S';
}
