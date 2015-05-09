#include "../../include/Player.h"

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

/**
 * Sets player name
 *
 * @param name Player's name
 */
void Player::setName(string name)
{
    this->_name = name;
}

/**
 * Returns current treasure
 */
int Player::getTreasure()
{
    return this->_treasureId;
}

/**
 * Sets new treasure for player to look for
 *
 * @param id Treasure Id
 */
void Player::setNewTreasure(int id)
{
    this->_treasureId = id;
    this->_score++;
}

/**
 * Sets previous treasure for player to look for
 *
 * @param id Previous treasure Id
 */
void Player::resetTreasure(int id)
{
    this->_treasureId = id;
    this->_score--;
}

/**
 * Returns player's score
 */
int Player::getScore()
{
    return this->_score;
}

/**
 * Returns player's row index
 */
int Player::row()
{
    return this->_row;
}

/**
 * Returns player's column index
 */
int Player::col()
{
    return this->_col;
}

/**
 * Changes player's location
 *
 * @param r Row index
 * @param c Column index
 */
void Player::setLocation(int r, int c)
{
    this->_row = r;
    this->_col = c;
}
