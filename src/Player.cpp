#include "../include/Player.h"

Player::Player()
{
    //ctor
}

Player::Player(string name)
{
    //ctor
    this->setName(name);
}

Player::~Player()
{
    //dtor
}

void Player::setName(string name)
{
    this->_name = name;
}

int Player::getTreasure()
{
    return this->_treasureId;
}

void Player::setNewTreasure(int tr)
{
    this->_treasureId = tr;
    this->_score++;
}

int Player::getScore()
{
    return this->_score;
}

int Player::row()
{
    return this->_row;
}

int Player::col()
{
    return this->_col;
}

void Player::setLocation(int r, int c)
{
    this->_row = r;
    this->_col = c;
}
