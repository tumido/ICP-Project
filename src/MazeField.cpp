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
 * ��dek
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
 * Navr�t� aktu�ln� kartu
 */
MazeCard MazeField::getCard()
{
    return this->_cardL;
}

/**
 * Vlo�� hrac� k�men na pol��ko
 */
void MazeField::putCard(MazeCard c)
{
    this->_cardL = c;
}
