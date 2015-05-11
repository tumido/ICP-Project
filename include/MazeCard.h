/**
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 */
#ifndef MAZECARD_H
#define MAZECARD_H

#include "common.h"

#include <string>

using namespace std;

class MazeCard
{
    public:
        MazeCard();
        MazeCard(string type);
        MazeCard(vector<string> props);
        virtual ~MazeCard();
        static MazeCard create(string type);
        enum CANGO { LEFT, UP, RIGHT, DOWN };
        bool canGo(MazeCard::CANGO dir);
        void turnRight();
        string type();
        int getTreasure();
        void setTreasure(int id);
        bool isTreasure();
        string getStringPath();
        string toString();
        static MazeCard fromString(string s);
    protected:
    private:
        string _type;
        void initPath();
        int _treasureId = -1;
        void setPath(string type);
        bool path[4];
};

#endif // MAZECARD_H
