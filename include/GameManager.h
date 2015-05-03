#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Action.h"
#include "MazeBoard.h"
#include "PathFinder.h"
#include "Player.h"

class GameManager
{
    public:
        GameManager();
        virtual ~GameManager();
        bool addPlayer(string name);
        bool remPlayer(string name);
        int  getSize();
        void setSize(int n);
        bool startGame();
        void restartGame();
        vector<MazeField> getMoves();
        bool moveCard(int r, int c);
        bool movePlayer(int r, int c);
        bool undo();
        int getActiveIndex();
        Player getActive();
        bool setTreasureCount(int n);
        bool save(string fname);
        bool load(string fname);
    protected:
    private:
        MazeBoard _board;
        void nextPlayer();
        Player _players[4];
        int _playerCount = 0;
        int _activePlayer = 0;
        int _size = 7;
        bool _started = false;
        vector<Action> _actions;
        int _treasureCount = 12;
        void generateTreasures();
        int takeTreasure();
        vector<int> _treasureIds;
};

#endif // GAMEMANAGER_H
