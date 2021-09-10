#include "../../include/blocks/JBlock.h"

JBlock::JBlock()
{
    coordinates_ = {0, 4};
    rotationTypes_ = {
        {{'J'},
         {'J', 'J', 'J'}},
        {{'J', 'J'},
         {'J'},
         {'J'}},
        {{'J', 'J', 'J'},
         {' ', ' ', 'J'}},
        {{' ', 'J'},
         {' ', 'J'},
         {'J', 'J'}}};

    currentRotation_ = 0;
    creationLevel_ = 0; //To-Do: modify after adding level
    blockChar_ = 'J';
}
