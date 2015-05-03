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
        void getTreasure();
        void setNewTreasure(Treasure tr);
        int getScore();
        int row();
        int col();
        void setLocation(int r, int c);
    protected:
    private:
         string _name;
         Treasure _treasure;
         int _row;
         int _col;
         int _score = 0;
};

#endif // PLAYER_H
