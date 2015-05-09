#include "../../include/MazeCard.h"
#include <iostream>
#include <stdio.h>

using namespace std;

MazeCard::MazeCard()
{
    this->_type = "-";
}

/**
 * Constructor
 * @param type Type of the card
 */
MazeCard::MazeCard(string type)
{
    this->initPath();
    this->_type = type;
    this->setPath(type);
}

MazeCard::~MazeCard()
{
    //dtor
}

/**
 * Creates new instance of MazeCard
 *
 * @param type Type of the card
 */
MazeCard MazeCard::create(string type)
{
    return MazeCard(type);
}

/**
 * Controls if there's path
 *
 * @param dir Path direction
 */
bool MazeCard::canGo(MazeCard::CANGO dir)
{
    return this->path[dir];
}

/**
 * Turns card to right
 */
void MazeCard::turnRight()
{
    bool newPath[4];
    for (int i = 0; i < 3; i++) {
        newPath[i + 1] = this->path[i];
    }
    newPath[0] = this->path[3];
    for (int i = 0; i < 4; i++)
        this->path[i] = newPath[i];
}

/**
 * Returns the type of a card
 */
string MazeCard::type()
{
    return this->_type;
}

/**
 * Returns treasure Id, -1 if there's none
 */
int MazeCard::getTreasure()
{
    return this->_treasureId;
}

/**
 * Sets treasure
 *
 * @param id Treasure Id
 */
void MazeCard::setTreasure(int id)
{
    this->_treasureId = id;
}

/**
 * Checks whether there's a treasure on the card.
 */
bool MazeCard::isTreasure()
{
    return this->_treasureId > - 1;
}

/**
 * Returns string representing current path
 */
string MazeCard::getStringPath()
{
    string ret;
    for (int i; i < 4; i++) {
        ret += (this->path[i]) ? "1" : "0";
    }
    return ret;
}

/**
 * Explicit initialization of the path array
 */
void MazeCard::initPath()
{
    for(int i = 0; i < 4; i++)
        this->path[i] = false;
}

/**
 * Sets path from the card
 *
 * @param type Card type
 */
void MazeCard::setPath(string type)
{
    if (type == "C") {
        this->path[LEFT] = true;
        this->path[UP] = true;
    } else if (type == "L") {
        this->path[LEFT] = true;
        this->path[RIGHT] = true;
    } else if (type == "F") {
        this->path[LEFT] = true;
        this->path[UP] = true;
        this->path[RIGHT] = true;
    }
}
