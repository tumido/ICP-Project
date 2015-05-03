#include "../include/MazeCard.h"
#include <iostream>
#include <stdio.h>

using namespace std;

/**
 *
 */
MazeCard::MazeCard()
{
    this->type = "-";
}

/**
 * Kontruktor
 * @param["type"] Typ vytv��en�ho kamene
 */
MazeCard::MazeCard(string type)
{
    this->initPath();
    this->type = type;
    this->setPath(type);
}

MazeCard::~MazeCard()
{
    //dtor
}

/**
 * Vytvo�en� nov� instance MazeCard
 */
MazeCard MazeCard::create(string type)
{
    return MazeCard(type);
}

/**
 * Kontrola mo�nosti v�chodu
 */
bool MazeCard::canGo(MazeCard::CANGO dir)
{
    return this->path[dir];
}

/**
 * Pooto�en� kamene o 90 stup�� doprava
 */
void MazeCard::turnRight()
{
    bool tmp = this->path[DOWN];
    for (int i = 0; i < 3; i++) {
        this->path[i + 1] = this->path[i];
    }
    this->path[0] = tmp;
}

/**
 * Explicitn� inicializace pole v�chod� z kamene
 */
void MazeCard::initPath()
{
    for(int i = 0; i < 4; i++)
        this->path[i] = false;
}

/**
 * Nastav� v�choz� hodnoty sm�ru cesty na kamenu
 * @param["type"] Typ kamene
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
