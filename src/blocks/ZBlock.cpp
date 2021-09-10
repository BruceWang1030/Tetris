#include "../../include/blocks/ZBlock.h"

ZBlock::ZBlock()
{
    coordinates_ = {0, 4};
    rotationTypes_ = {
        {{'Z', 'Z', ' '},
         {' ', 'Z', 'Z'}},
        {{' ', 'Z'},
         {'Z', 'Z'},
         {'Z', ' '}},
        {{'Z', 'Z', ' '},
         {' ', 'Z', 'Z'}},
        {{' ', 'Z'},
         {'Z', 'Z'},
         {'Z', ' '}}};

    currentRotation_ = 0;
    creationLevel_ = 0; //To-Do: modify after adding level
    blockChar_ = 'Z';
}
