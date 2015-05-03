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
    protected:
    private:
        MazeBoard _board;
        Player _players[4];
        int _playerCount = 0;
        int _size = 7;
        bool _started = false;
        int _activePlayer = 0;
        vector<Action> _actions;
        void nextPlayer();
};

#endif // GAMEMANAGER_H
