/**
 * @file OutputCLI.cpp
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief CIL output drawing
 */
#include "../include/OutputCLI.h"

using namespace std;

OutputCLI::OutputCLI(GameManager *manager)
{
    //ctor
    this->game = manager;
}

OutputCLI::~OutputCLI()
{
    //dtor
    if (buffer != NULL)
        delete [] buffer;
}


/**
 * Allocates memory for cards
 */
void OutputCLI::load()
{
    if (buffer != NULL)
        delete [] buffer;

    int boardSize = this->game->getSize();
    this->buffer = new char[3 * boardSize * 3 * boardSize];
}

/**
 * Draws scene to command line
 */
void OutputCLI::draw()
{
    this->prep();
    int lim = 3 * this->game->getSize();
    for (int j = 0; j < lim; j++) {
        for (int i = 0; i < lim; i++) {
            cout << this->buffer[i + lim * j];
        }
        cout << endl;
    }
    cout << endl;

    auto card = this->game->getBoard().getFreeCard();
    auto freeCard = this->cardString(card);
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            cout << freeCard[i + 3*j];
        }
        cout << endl;
    }
    delete [] freeCard;
}

/**
 * Writes card to buffer
 */
void OutputCLI::cardToBuffer(MazeField mf)
{
    auto currCard = mf.getCard();
    auto card = this->cardString(currCard);
    auto len = this->game->getSize();
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            //i + R * 3*len + 3*C + j * len
            this->buffer[i + 3*mf.row() * 3*len + 3*mf.col() + j * 3 * len] = card[i + j * 3];
        }
    }
    delete [] card;
}

/**
 * Converts card to 3x3 char array
 *
 * @param mf Field to convert
 */
char * OutputCLI::cardString(MazeCard &mc)
{
    auto card = new char[9];
    //upper side
    card[0] = '#';
    card[1] = mc.canGo(MazeCard::CANGO::UP) ? ' ' : '#';
    card[2] = '#';
    //mid
    card[3] = mc.canGo(MazeCard::CANGO::LEFT) ? ' ' : '#';
    if (mc.isTreasure()) {
        card[4] = ((char)mc.getTreasure()) + 'A';
    } else {
        card[4] = ' ';
    }
    card[5] = mc.canGo(MazeCard::CANGO::RIGHT) ? ' ' : '#';
    //down
    card[6] = '#';
    card[7] = mc.canGo(MazeCard::CANGO::DOWN) ? ' ' : '#';
    card[8] = '#';

    return card;
}

/**
 * Puts players to buffer
 */
void OutputCLI::putPlayers()
{
    int len = this->game->getSize();
    auto players = this->game->getAllPlayers();
    for (unsigned int i = 0; i < players.size(); i++) {
        if (i == game->getActiveIndex()) {
            cout << "X ";
        } else {
            cout << "  ";
        }
        cout << players[i].getName() << ": " << players[i].getTreasure() + 'A' << endl;
        this->buffer[1 + 3 * players[i].col() + 3 *  players[i].row() * 3*len + 3*len] = ((char)i) + '0';
    }
}

/**
 * Puts actual gamestate to buffer
 */
void OutputCLI::prep()
{
    for (int r = 0; r < this->game->getSize(); r++) {
        for (int c = 0; c < this->game->getSize(); c++) {
            this->cardToBuffer(this->game->getBoard().get(r, c));
        }
    }
    this->putPlayers();
}
