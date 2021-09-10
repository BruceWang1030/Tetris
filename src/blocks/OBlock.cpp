#include "../../include/blocks/OBlock.h"

OBlock::OBlock()
{
    coordinates_ = {0, 4};
    rotationTypes_ = {
        {{'O', 'O'},
         {'O', 'O'}},
        {{'O', 'O'},
         {'O', 'O'}},
        {{'O', 'O'},
         {'O', 'O'}},
        {{'O', 'O'},
         {'O', 'O'}}};

    currentRotation_ = 0;
    creationLevel_ = 0; //To-Do: modify after adding level
    blockChar_ = 'O';
}
