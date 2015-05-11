/**
 * @file Action.cpp
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Defines the action done on one turn
 */
#include "../include/Action.h"

Action::Action(TYPE type, int r, int c)
{
    //ctor
    this->_type = type;
    this->_row = r;
    this->_col = c;
}

Action::~Action()
{
    //dtor
}

/**
 * @brief Returns row index
 */
int Action::row()
{
    return this->_row;
}

/**
 * @brief Returns column index
 */
int Action::col()
{
    return this->_col;
}

/**
 * @brief Returns action type
 */
Action::TYPE Action::type()
{
    return this->_type;
}
