/**
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 */
#include "../../include/Action.h"

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
 * Returns row index
 */
int Action::row()
{
    return this->_row;
}

/**
 * Returns column index
 */
int Action::col()
{
    return this->_col;
}

/**
 * Returns action type
 */
Action::TYPE Action::type()
{
    return this->_type;
}
