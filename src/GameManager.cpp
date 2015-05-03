#include "../include/GameManager.h"

GameManager::GameManager()
{
    //ctor
}

GameManager::~GameManager()
{
    //dtor
}

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

bool GameManager::remPlayer(string name)
{
    return false;
}

int GameManager::getSize()
{
    return this->_size;
}

void GameManager::setSize(int n)
{
    if (n <= 5 && n <= 11 && n % 2 == 1)
        this->_size = n;
}

bool GameManager::startGame()
{
    if (this->_playerCount >= 2) {
        this->_board = MazeBoard(this->_size);
        this->_started = true;
    }
    return this->_started;
}

void GameManager::restartGame()
{
    this->_board.newGame();
}

vector<MazeField> GameManager::getMoves()
{
    Player active = this->getActive();
    MazeField mf = this->_board.get(active.row(), active.col());
    return PathFinder::possibleMoves(mf, this->_board);
}

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

bool GameManager::movePlayer(int r, int c)
{
    MazeField mf = this->_board.get(r, c);
    if (mf.row() > -1) {
        auto moves = this->getMoves();
        if (PathFinder::containsField(mf, moves)) {
            this->_players[this->getActiveIndex()].setLocation(mf.row(), mf.col());
            //TODO: Check Treasure
            this->nextPlayer();
            return true;
        }
    }
    return false;
}

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

void GameManager::nextPlayer()
{
    this->_activePlayer = (this->_activePlayer + 1) % 4;
}

int GameManager::getActiveIndex()
{
    return this->_activePlayer;
}

Player GameManager::getActive()
{
    return this->_players[this->getActiveIndex()];
}
