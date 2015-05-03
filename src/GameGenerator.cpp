#include "../include/GameGenerator.h"

GameGenerator::GameGenerator()
{
    //ctor
}

GameGenerator::~GameGenerator()
{
    //dtor
}

/**
 * Generátor kamene
 */
MazeCard GameGenerator::generateCard()
{
    string s;
    switch (rand() % 3) {
    case 0:
        s = "C";
        break;
    case 1:
        s = "L";
        break;
    case 2:
        s = "F";
        break;
    default:
        break;
    }
    return MazeCard(s);
}

/**
 * Generátor více kamenù
 */
vector<MazeCard> GameGenerator::generateCards(int n)
{
    vector<MazeCard> cards;
    for (int i = 0; i < n; i++) {
        cards.push_back(GameGenerator::generateCard());
    }
    return cards;
}

