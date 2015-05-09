#include "../../include/MazeField.h"

MazeField::MazeField(int r, int c)
{
    //ctor
    this->_row = r;
    this->_col = c;
}

MazeField::~MazeField()
{
    //dtor
}

/**
 * Returns Row index
 */
int MazeField::row()
{
    return this->_row;
}

/**
 * Returns Column index
 */
 int MazeField::col()
 {
     return this->_col;
 }

/**
 * Returns card, that is on field
 */
MazeCard MazeField::getCard()
{
    return this->_cardL;
}

/**
 * Returns reference to current card
 */
MazeCard *MazeField::getCardP()
{
    return &this->_cardL;
}

/**
 * Places card on field
 */
void MazeField::putCard(MazeCard c)
{
    this->_cardL = c;
}
