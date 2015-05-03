#include "../include/MazeBoard.h"

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
 * Vytvoøí hrací plochu o velikosti n
 */
MazeBoard MazeBoard::createMazeBoard(int n)
{
    return MazeBoard(n);
}

/**
 * vytvoøí novou hrací plochu
 */
void MazeBoard::newGame()
{
    int lenFields = this->_fields.size();
    vector<MazeCard> cards = GameGenerator::generateCards(lenFields);
    for (int i; i < lenFields; i++) {
        this->_fields[i].putCard(cards[i]);
    }
    this->_freeCard = GameGenerator::generateCard();
}

/**
 * Vrací políèko na pozici [r, c]
 */
MazeField MazeBoard::get(int r, int c)
{
    int index = c + r * this->rowLen;
    if (this->_fields.size() > index)
        return this->_fields[index];
    else
        return MazeField(-1,-1);
}

/**
 * Vrací volný kámen.
 */
MazeCard MazeBoard::getFreeCard()
{
    return this->_freeCard;
}

/**
 * Provede se vložení políèka na pozici políèka mf.
 */
void MazeBoard::shift(MazeField mf)
{
    MazeCard tmpCard = mf.getCard();
    // dolù ve sloupci C
    int bound = this->rowLen - 1;
    if (mf.row() == 0 && mf.col() % 2 == 1) {
        this->shiftDown(mf.col());
    //nahorù ve sloupci C
    } else if (mf.row() == bound && mf.col() % 2 == 1) {
        shiftUp(mf.col());
    //doprava na øádku R
    } else if (mf.col() == 0 && mf.row() % 2 == 1) {
        shiftRight(mf.row());
    //doleva na øádku R
    } else if (mf.row() == bound && mf.col() % 2 == 1) {
        shiftLeft(mf.row());
    }
}

/**
 * Posune urèitý sloupec dolù
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
 * Posune urèitý sloupec nahorù
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
 * Posune urèitý øádek doprava
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
 * Posune urèitý øádek doleva
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
 * Ziska kamen z urciteho policka
 */
MazeCard MazeBoard::getCard(int r, int c)
{
    return this->get(r, c).getCard();
}

/**
 * Vlozi kamen na urcite policko
 */
void MazeBoard::putCard(int r, int c, MazeCard card)
{
    return this->get(r,c).putCard(card);
}
