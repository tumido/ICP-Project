#include "../../include/MazeBoard.h"

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
void MazeBoard::shift(MazeField mf)
{
    MazeCard tmpCard = mf.getCard();
    //down
    int bound = this->rowLen - 1;
    if (mf.row() == 0 && mf.col() % 2 == 1) {
        this->shiftDown(mf.col());
    //up
    } else if (mf.row() == bound && mf.col() % 2 == 1) {
        shiftUp(mf.col());
    //right
    } else if (mf.col() == 0 && mf.row() % 2 == 1) {
        shiftRight(mf.row());
    //left
    } else if (mf.row() == bound && mf.col() % 2 == 1) {
        shiftLeft(mf.row());
    }
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
        MazeField curCard = this->get(row, c);
        curCard.putCard(this->getCard(row - 1, c));
    }
    this->get(0, c).putCard(this->_freeCard);
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
        MazeField curCard = this->get(row, c);
        curCard.putCard(this->getCard(row + 1, c));
    }
    this->get(bound, c).putCard(this->_freeCard);
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
    MazeCard tmpCard = this->getCard(r, bound);
    for (int col = 0; col < bound; col++) {
        MazeField curCard = this->get(r, col);
        curCard.putCard(this->getCard(r, col + 1));
    }
    this->get(r, bound).putCard(this->_freeCard);
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
    MazeCard tmpCard = this->getCard(r, 0);
    for (int col = bound; col > 0; col--) {
        MazeField curCard = this->get(r, col);
        curCard.putCard(this->getCard(r, col - 1));
    }
    this->get(r, 0).putCard(this->_freeCard);
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
 * Places card at [r, c]
 *
 * @param r Row index
 * @param c Column index
 * @param card Card to insert
 */
void MazeBoard::putCard(int r, int c, MazeCard card)
{
    return this->get(r,c).putCard(card);
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
    this->getCard(r, c).setTreasure(id);
}

/**
 * Places treasures to the board
 *
 * @param treasures Vector of treasure Ids.
 */
void MazeBoard::placeTreasures(vector<int> treasures)
{
    vector<MazeField> fields(this->_fields);
    random_shuffle(fields.begin(), fields.end());
    while(treasures.size() > 0) {
        auto treasure = treasures.back();
        treasures.pop_back();
        MazeField mf = fields.back();
        fields.pop_back();
        this->placeTreasure(mf.row(), mf.col(), treasure);
    }
}
