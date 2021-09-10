#include "../../include/blocks/TBlock.h"

TBlock::TBlock()
{
    coordinates_ = {0, 4};
    rotationTypes_ = {
        {{'T', 'T', 'T'},
         {' ', 'T', ' '}},
        {{' ', 'T'},
         {'T', 'T'},
         {' ', 'T'}},
        {{' ', 'T', ' '},
         {'T', 'T', 'T'}},
        {{'T', ' '},
         {'T', 'T'},
         {'T', ' '}}};

    currentRotation_ = 0;
    creationLevel_ = 0; //To-Do: modify after adding level
    blockChar_ = 'T';
}
