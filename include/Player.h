#ifndef PLAYER_H
#define PLAYER_H

#include "Treasure.h"

#include <string>

using namespace std;

class Player
{
    public:
        Player();
        Player(string name);
        virtual ~Player();
        void setName(string name);
        int getTreasure();
        void setNewTreasure(int id);
        void resetTreasure(int id);
        int getScore();
        int row();
        int col();
        void setLocation(int r, int c);
    protected:
    private:
         string _name;
         int _treasureId;
         int _row;
         int _col;
         int _score = 0;
};

#endif // PLAYER_H
