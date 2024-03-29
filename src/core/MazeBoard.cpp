/**
 * @file MazeBoard.cpp
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Class defining the board of the game
 */
#include "../include/MazeBoard.h"

#include <iostream>

MazeBoard::MazeBoard()
{

}

MazeBoard::MazeBoard(int n)
{
    //ctor
    this->rowLen = n;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            this->_fields.push_back(MazeField(r, c));
        }
    }
    this->newGame();
}

MazeBoard::~MazeBoard()
{
    //dtor
}

/**
 * Creates maze board
 *
 * @param n size of board
 */
MazeBoard MazeBoard::createMazeBoard(int n)
{
    return MazeBoard(n);
}

/**
 * Creates new game
 */
void MazeBoard::newGame()
{
    int lenFields = this->_fields.size();
    vector<MazeCard> cards = GameGenerator::generateCards(lenFields);
    for (int i = 0; i < lenFields; i++) {
        this->_fields[i].putCard(cards[i]);
    }
    this->_freeCard = GameGenerator::generateCard();
    this->defaultCards();
}

/**
 * Return maze field located at [r, c]
 *
 * @param r Row index
 * @param c Column index
 */
MazeField MazeBoard::get(int r, int c)
{
    unsigned int index = c + r * this->rowLen;
    if (this->_fields.size() > index)
        return this->_fields[index];
    else
        return MazeField(-1,-1);
}

/**
 * Returns reference to MazeField
 *
 * @param r Row index
 * @param c Column index
 */
MazeField *MazeBoard::getP(int r, int c)
{
    unsigned int index = c + r * this->rowLen;
    if (this->_fields.size() > index)
        return &this->_fields[index];
    else
        return NULL;
}

/**
 * Returns free card
 */
MazeCard MazeBoard::getFreeCard()
{
    return this->_freeCard;
}

/**
 * Inserts card to MazeField
 *
 * @param mf MazeCard to which the card will be inserted
 */
bool MazeBoard::shift(MazeField mf, bool undo)
{
    MazeCard tmpCard = mf.getCard();
    //down
    int bound = this->rowLen - 1;
    if (undo || this->canPlay(mf)) {
        if (mf.row() == 0 && mf.col() % 2 == 1) {
            shiftDown(mf.col());
            this->_previous = mf;
            return true;
        //up
        } else if (mf.row() == bound && mf.col() % 2 == 1) {
            shiftUp(mf.col());
            this->_previous = mf;
            return true;
        //right
        } else if (mf.col() == 0 && mf.row() % 2 == 1) {
            shiftLeft(mf.row());
            this->_previous = mf;
            return true;
        //left
        } else if (mf.col() == bound && mf.row() % 2 == 1) {
            shiftRight(mf.row());
            this->_previous = mf;
            return true;
        }
    }
    return false;
}

/**
 * Shifts column down
 *
 * @param c Column index
 */
void MazeBoard::shiftDown(int c)
{
    int bound = this->rowLen - 1;
    MazeCard tmpCard = this->getCard(bound, c);
    for (int row = bound; 0 < row; row--) {
        this->putCard(row, c, this->getCard(row - 1, c));
    }
    this->putCard(0, c, this->_freeCard);
    this->_freeCard = tmpCard;
}

/**
 * Shifts column up
 *
 * @param c Column index
 */
void MazeBoard::shiftUp(int c)
{
    int bound = this->rowLen - 1;
    MazeCard tmpCard = this->getCard(0, c);
    for (int row = 0; row < bound; row++) {
        this->putCard(row, c, this->getCard(row + 1, c));
    }
    this->putCard(bound, c, this->_freeCard);
    this->_freeCard = tmpCard;
}

/**
 * Shifts row to the right
 *
 * @param r Row index
 */
void MazeBoard::shiftRight(int r)
{
    int bound = this->rowLen - 1;
    MazeCard tmpCard = this->getCard(r, 0);
    for (int col = 0; col < bound; col++) {
        this->putCard(r, col, this->getCard(r, col + 1));
    }
    this->putCard(r, bound, this->_freeCard);
    this->_freeCard = tmpCard;
}

/**
 * Shifts row to the left
 *
 * @param r Row index
 */
void MazeBoard::shiftLeft(int r)
{
    int bound = this->rowLen - 1;
    MazeCard tmpCard = this->getCard(r, bound);
    for (int col = bound; col > 0; col--) {
        this->putCard(r, col, this->getCard(r, col - 1));
    }
    this->putCard(r, 0, this->_freeCard);
    this->_freeCard = tmpCard;
}

/**
 * Returns card located at [r, c]
 *
 * @param r Row index
 * @param c Column index
 */
MazeCard MazeBoard::getCard(int r, int c)
{
    return this->get(r, c).getCard();
}

/**
 * Returns reference to card located at [r, c]
 *
 * @param r Row index
 * @param c Column index
 */
MazeCard *MazeBoard::getCardP(int r, int c)
{
    return this->getP(r, c)->getCardP();
}

/**
 * Places card at [r, c]
 *
 * @param r Row index
 * @param c Column index
 * @param card Card to insert
 */
void MazeBoard::putCard(int r, int c, MazeCard card)
{
    return this->getP(r,c)->putCard(card);
}

/**
 * Sets treasure to card
 *
 * @param r Row index
 * @param c Column index
 * @param id Treasure Id
 */
void MazeBoard::placeTreasure(int r, int c, int id)
{
    this->getCardP(r, c)->setTreasure(id);
}

/**
 * Default cards
 */
void MazeBoard::defaultCards()
{
    auto bound = this->rowLen - 1;
    MazeCard card("C");
    this->getP(bound, bound)->putCard(card);
    card.turnRight();
    this->getP(0, bound)->putCard(card);
    card.turnRight();
    this->getP(0, 0)->putCard(card);
    card.turnRight();
    this->getP(bound, 0)->putCard(card);

    MazeCard card2("F");
    for (int i = 2; i < bound; i += 2) {
        this->getP(i, bound)->putCard(card2);
        card2.turnRight();
        this->getP(0, i)->putCard(card2);
        card2.turnRight();
        this->getP(i, 0)->putCard(card2);
        card2.turnRight();
        this->getP(bound, i)->putCard(card2);
        card2.turnRight();
    }
}

/**
 * Places treasures to the board
 *
 * @param treasures Vector of treasure Ids.
 */
void MazeBoard::placeTreasures(vector<int> treasures)
{
    vector<MazeField> fields(this->_fields);
    random_shuffle(fields.begin(), fields.end(), [](int i){ return rand() % i; });
    while(treasures.size() > 0) {
        auto treasure = treasures.back();
        treasures.pop_back();
        MazeField mf = fields.back();
        fields.pop_back();
        this->placeTreasure(mf.row(), mf.col(), treasure);
    }
}

/**
 * Turns free card to the right
 */
void MazeBoard::turnFreeCard()
{
    this->_freeCard.turnRight();
}

/**
 * Serializes board
 */
string MazeBoard::toString()
{
    ostringstream serial;
    serial << this->rowLen << ";";
    for (int r = 0; r < this->rowLen; r++) {
        for (int c = 0; c < this->rowLen; c++) {
            serial << this->getCard(r, c).toString();
        }
    }
    serial << this->getFreeCard().toString();
    return serial.str();
}

/**
 * Sets free card
 */
void MazeBoard::setFreeCard(MazeCard card)
{
    this->_freeCard = card;
}

/**
 * Returns row length
 */
int MazeBoard::getSize()
{
    return this->rowLen;
}

/**
 * Checks whether the card can be played
 *
 * @param mf Current MazeField
 */
bool MazeBoard::canPlay(MazeField mf)
{
    int bound = this->rowLen - 1;
    if (mf.row() == this->_previous.row() &&
        ((mf.col() == 0 && this->_previous.col() == bound) ||
         (mf.col() == bound && this->_previous.col() == 0)))
        return false;
    if (mf.col() == this->_previous.col() &&
        ((mf.row() == 0 && this->_previous.row() == bound) ||
         (mf.row() == bound && this->_previous.row() == 0)))
        return false;
    return true;
}
