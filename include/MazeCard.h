#ifndef MAZECARD_H
#define MAZECARD_H

#include <string>

using namespace std;

class MazeCard
{
    public:
        MazeCard();
        MazeCard(string type);
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
    protected:
    private:
        string _type;
        void initPath();
        int _treasureId = -1;
        void setPath(string type);
        bool path[4];
};

#endif // MAZECARD_H
