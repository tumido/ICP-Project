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
