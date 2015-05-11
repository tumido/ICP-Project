/**
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 */
#include "../../include/Player.h"

using namespace std;

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
 * Returns player's name
 */
string Player::getName()
{
    return this->_name;
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
unsigned int Player::getScore()
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

/**
 * Serializes player
 */
string Player::toString()
{
    ostringstream serial;
    serial << this->_name << "/";
    serial << this->_treasureId << "/";
    serial << this->_row << "/";
    serial << this->_col << "/";
    serial << this->_score << ";";
    return serial.str();
}

/**
 * Deserializes player
 */
Player Player::fromString(string s)
{
    auto values = split(s, '/');
    Player player(values[0]);
    player.setNewTreasure(atoi(values[1].c_str()));
    player.setLocation(atoi(values[2].c_str()), atoi(values[3].c_str()));
    player.setScore(atoi(values[4].c_str()));
    return player;
}

/**
 * Sets current player's score
 *
 * @param s Score
 */
void Player::setScore(int s)
{
    this->_score = s;
}
