#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

#include <string>
#include <sstream>

using namespace std;

class Player
{
    public:
        Player();
        Player(string name);
        virtual ~Player();
        string getName();
        void setName(string name);
        int getTreasure();
        void setNewTreasure(int id);
        void resetTreasure(int id);
        unsigned int getScore();
        int row();
        int col();
        void setLocation(int r, int c);
        string toString();
        static Player fromString(string s);
        void setScore(int s);
    protected:
    private:
         string _name;
         int _treasureId;
         int _row;
         int _col;
         unsigned int _score = -1;
};

#endif // PLAYER_H
