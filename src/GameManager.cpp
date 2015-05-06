#include "../include/GameManager.h"

GameManager::GameManager()
{
    //ctor
}

GameManager::~GameManager()
{
    //dtor
}


/**
 * Adds player to the game
 *
 * @param name Player's name
 */
bool GameManager::addPlayer(string name)
{
    if (this->_playerCount < 4) {
        this->_players[this->_playerCount] = Player(name);
        this->_playerCount++;
        return true;
    } else {
        return false;
    }
}

/**
 * Removes player from the game
 *
 * @param name Player's name
 */
bool GameManager::remPlayer(string name)
{
    return false;
}

/**
 * Returns size of the board
 * default value is 7
 */
int GameManager::getSize()
{
    return this->_size;
}

/**
 * Nastaví velikost hrací plochy
 *
 * @param n Size of board, value should be between 5 and 11
 */
void GameManager::setSize(int n)
{
    if (n <= 5 && n <= 11 && n % 2 == 1)
        this->_size = n;
}

/**
 * Starts the game
 */
bool GameManager::startGame()
{
    if (this->_playerCount >= 2) {
        this->_board = MazeBoard(this->_size);
        this->generateTreasures();
        this->_started = true;
    }
    return this->_started;
}

/**
 * Restarts the game
 */
void GameManager::restartGame()
{
    this->_board.newGame();
}

/**
 * Returns vector with all possible moves
 */
vector<MazeField> GameManager::getMoves()
{
    Player active = this->getActive();
    MazeField mf = this->_board.get(active.row(), active.col());
    return PathFinder::possibleMoves(mf, this->_board);
}

/**
 * Moves card
 *
 * @param r Row index
 * @param c Column index
 */
bool GameManager::moveCard(int r, int c)
{
    MazeField field = this->_board.get(r, c);
    if (field.row() > -1) {
        this->_board.shift(field);
        this->_actions.push_back(Action(Action::TYPE::MOVE_CARD, r, c));
        return true;
    } else {
        return false;
    }
}

/**
 * Moves player to different field
 *
 * @param r Row index
 * @param c Column index
 */
bool GameManager::movePlayer(int r, int c)
{
    MazeField mf = this->_board.get(r, c);
    if (mf.row() > -1) {
        auto moves = this->getMoves();
        if (PathFinder::containsField(mf, moves)) {
            this->_players[this->getActiveIndex()].setLocation(mf.row(), mf.col());
            if(mf.getCard().getTreasure() == this->getActive().getTreasure()) {
                int newId = this->takeTreasure();
                this->_players[this->getActiveIndex()].setNewTreasure(newId);
            }
            this->nextPlayer();
            return true;
        }
    }
    return false;
}

/**
 * Reverts last move
 */
bool GameManager::undo()
{
    if (this->_actions.size() > 0) {
        Action toRevert = this->_actions.back();
        this->_actions.pop_back();
        //TODO:
        return true;
    } else {
        return false;
    }
}

/**
 * Sets next player as active
 */
void GameManager::nextPlayer()
{
    this->_activePlayer = (this->_activePlayer + 1) % 4;
}

/**
 * Returns index of the active player
 */
int GameManager::getActiveIndex()
{
    return this->_activePlayer;
}

/**
 * Returns active player
 */
Player GameManager::getActive()
{
    return this->_players[this->getActiveIndex()];
}

/**
 * Sets treasure count
 *
 * @param n New treasure count
 */
bool GameManager::setTreasureCount(int n)
{
    if (n == 24 || n == 12) {
        this->_treasureCount = n;
        return true;
    } else {
        return false;
    }
}

/**
 * Saves current game to file
 *
 * @param fname File name
 */
bool GameManager::save(string fname)
{
    return false;
}

/**
 * Loads game from file
 *
 * @param fname File name
 */
bool GameManager::load(string fname)
{
    return false;
}

/**
 * Generates new treasures
 */
void GameManager::generateTreasures()
{
    this->_treasureIds = vector<int>();
    for (int i = 0; i < this->_treasureCount; i++) {
        this->_treasureIds.push_back(i);
    }
}

/**
 * Takes treasure from deck
 */
int GameManager::takeTreasure()
{
    if (this->_treasureIds.size() > 0) {
        int id = this->_treasureIds.back();
        this->_treasureIds.pop_back();
        return id;
    } else {
        return -1;
    }
}
