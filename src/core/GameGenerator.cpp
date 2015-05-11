/**
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 */
#include "../../include/GameGenerator.h"

GameGenerator::GameGenerator()
{
    //ctor
}

GameGenerator::~GameGenerator()
{
    //dtor
}

/**
 * Generates card
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
    MazeCard card(s);
    int rotates = rand() % 4;
    for (int i = 0; i < rotates; i++)
        card.turnRight();
    return card;
}

/**
 * Generates cards
 *
 * @param n Count
 */
vector<MazeCard> GameGenerator::generateCards(int n)
{
    vector<MazeCard> cards;
    for (int i = 0; i < n; i++) {
        cards.push_back(GameGenerator::generateCard());
    }
    return cards;
}

