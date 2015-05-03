#include "../include/MazeField.h"

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
 * Øádek
 */
int MazeField::row()
{
    return this->_row;
}

/**
 * Sloupec
 */
 int MazeField::col()
 {
     return this->_col;
 }

/**
 * Navrátí aktuální kartu
 */
MazeCard MazeField::getCard()
{
    return this->_cardL;
}

/**
 * Vloží hrací kámen na políèko
 */
void MazeField::putCard(MazeCard c)
{
    this->_cardL = c;
}
