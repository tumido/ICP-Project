#include "../../include/GameManager.h"

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
    if (this->_players.size() < 4) {
        this->_players.push_back(Player(name));
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
 * Sets size of board
 *
 * @param n Size of board, value should be between 5 and 11
 */
bool GameManager::setSize(int n)
{
    if (n >= 5 && n <= 11 && n % 2 == 1) {
        this->_size = n;
        return true;
    } else {
        return false;
    }
}

/**
 * Starts the game
 */
bool GameManager::startGame()
{
    if (this->_players.size() >= 2) {
        this->_board = MazeBoard(this->_size);
        this->generateTreasures();
        this->playerAutoPlacement();
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
    this->playerAutoPlacement();
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
        this->fixPlayerPositions(r, c);
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
            int p_row = this->_players[this->getActiveIndex()].row();
            int p_col = this->_players[this->getActiveIndex()].col();
            this->_actions.push_back(Action(Action::TYPE::MOVE_PLAYER, p_row, p_col));
            this->_players[this->getActiveIndex()].setLocation(mf.row(), mf.col());
            if(mf.getCard().getTreasure() == this->getActive().getTreasure()) {
                int oldId = mf.getCard().getTreasure();
                int newId = this->takeTreasure();
                this->_players[this->getActiveIndex()].setNewTreasure(newId);
                if (this->getActive().getScore() >= this->_treasureCount / this->_players.size()) {
                    this->_won = true;
                }
                this->_actions.push_back(Action(Action::TYPE::TAKE_TREASURE, newId, oldId));
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
        if (toRevert.type() == Action::TYPE::MOVE_PLAYER) {
            this->revertPlayer(toRevert);
        } else {
            this->revertCard(toRevert);
        }
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
    this->_activePlayer = (this->_activePlayer + 1) % this->_players.size();
}

/**
 * Sets previous player as activeě
 */
void GameManager::previousPlayer()
{
    this->_activePlayer = (this->_activePlayer + this->_players.size() - 1) % this->_players.size();
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
 * Returns vector of Player
 */
vector<Player> GameManager::getAllPlayers()
{
    return this->_players;
}

/**
 * Returns vector of player names
 */
vector<string> GameManager::getNames()
{
    vector<string> names;
    for(unsigned int i = 0; i < this->_players.size(); i++)
        names.push_back(this->_players[i].getName());
    return names;
}

/**
 * Returns string representing card's path
 *
 * @param r Row index
 * @param c Column index
 */
string GameManager::getCardPath(int r, int c)
{
    return this->_board.get(r, c).getCard().getStringPath();
}

/**
 * Returns free card
 */
string GameManager::getFreeCard()
{
    return this->_board.getFreeCard().getStringPath();
}

/**
 * Returns game board
 */
MazeBoard GameManager::getBoard()
{
    return this->_board;
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
    random_shuffle(this->_treasureIds.begin(), this->_treasureIds.end());
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

/**
 * Adjusts players on mazeboard
 *
 * @param r Row index
 * @param c Column index
 */
void GameManager::fixPlayerPositions(int r, int c)
{
    for (unsigned int i = 0; i < this->_players.size(); i++)
        this->fixPlayerPosition(r, c, i);
}

/**
 * Adjusts player's position
 *
 * @param r Row index
 * @param c Column index
 * @param id Player's index
 */
void GameManager::fixPlayerPosition(int r, int c, int id)
{
    int lim = this->_size - 1;
    int current_row = this->_players[id].row();
    int current_col = this->_players[id].col();

    if (this->_players[id].row() == r && r != 0 && r != lim) {
        if (c == 0) {
            this->_players[id].setLocation(this->fixPositionBounds(current_row + 1), current_col);
        } else if (c == lim) {
            this->_players[id].setLocation(this->fixPositionBounds(current_row - 1), current_col);
        }
    } else if (this->_players[id].col() == c && c != 0 && c != lim) {
        if (r == 0) {
            this->_players[id].setLocation(current_row, this->fixPositionBounds(current_col + 1));
        } else if (r == lim) {
            this->_players[id].setLocation(current_row, this->fixPositionBounds(current_col - 1));
        }
    }
}

/**
 * Adjusts position to stay inside MazeBoard
 *
 * @param i Index
 */
int GameManager::fixPositionBounds(int i)
{
    return (i + this->_size) % this->_size;
}

/**
 * Reverts card move
 */
void GameManager::revertCard(Action action)
{
    int c = action.col();
    int r = action.row();
    int lim = this->_size - 1;

    if (c == 0) {
        c = lim;
    } else if (c == lim) {
        c = 0;
    }

    if (r == 0) {
        r = lim;
    } else if (r == lim) {
        r = 0;
    }

    this->_actions.pop_back();
    this->_actions.pop_back();
}

/**
 * Reverts player move
 */
void GameManager::revertPlayer(Action action)
{
    this->previousPlayer();
    if (action.type() == Action::TYPE::TAKE_TREASURE) {
        this->_players[this->getActiveIndex()].resetTreasure(action.col());
        this->_treasureIds.push_back(action.row());
        this->nextPlayer();
        this->_actions.pop_back();
        this->revertPlayer(this->_actions.back());
    } else {
        this->movePlayer(action.row(), action.col());
        this->_actions.pop_back();
        this->_actions.pop_back();
    }
}

/**
 * Places players on default locations
 */
void GameManager::playerAutoPlacement()
{
    auto cnt = this->_players.size();
    auto lim = this->_size - 1;
    if (cnt > 0)
        this->_players[0].setLocation(0, 0);
    if (cnt > 1)
        this->_players[1].setLocation(lim, lim);
    if (cnt > 2)
        this->_players[2].setLocation(0, lim);
    if (cnt > 3)
        this->_players[3].setLocation(lim, 0);
}
bool GameManager::isStarted()
{
    return _started;
}
