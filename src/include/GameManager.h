/**
 * @file GameManager.h
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Main Core interface accessible for front-end
 */
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <algorithm>

#include "Action.h"
#include "MazeBoard.h"
#include "PathFinder.h"
#include "Player.h"

/// @brief Game class that manages all the game logic
class GameManager
{
    public:
        GameManager();
        virtual ~GameManager();
        bool addPlayer(string name);
        int  getSize();
        bool setSize(int n);
        bool startGame();
        void restartGame();
        vector<MazeField> getMoves();
        bool moveCard(int r, int c, bool undo = false);
        bool movePlayer(int r, int c);
        bool undo();
        int getActiveIndex();
        Player getActive();
        bool setTreasureCount(int n);
        bool save(string fname);
        bool load(string fname);
        vector<Player> getAllPlayers();
        bool isWon();
        bool isStarted();
        MazeBoard getBoard();
        vector<string> getNames();
        string getCardPath(int r, int c);
        string getFreeCard();
        void turnFreeCard();
        bool isTreasure(int r, int c);
        int getTreasure(int r, int c);
        bool isFreeTreasure();
        int getFreeTreasure();
    protected:
    private:
        MazeBoard _board;
        bool _won = false;
        void nextPlayer();
        void previousPlayer();
        vector<Player> _players;
        int _activePlayer = 0;
        int _size = 7;
        bool _started = false;
        vector<Action> _actions;
        int _treasureCount = 12;
        void generateTreasures();
        int takeTreasure();
        vector<int> _treasureIds;
        void fixPlayerPositions(int r, int c);
        void fixPlayerPosition(int r, int c, int id);
        int fixPositionBounds(int i);
        void revertCard(Action action);
        void revertPlayer(Action action);
        void playerAutoPlacement();
        void playerDefaultTreasures();
};

#endif // GAMEMANAGER_H
