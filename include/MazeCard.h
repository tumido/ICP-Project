#ifndef MAZECARD_H
#define MAZECARD_H
#include <string>

using namespace std;

class MazeCard
{
    public:
        MazeCard();
        MazeCard(string);
        virtual ~MazeCard();
        static MazeCard create(string type);
        enum CANGO { LEFT, UP, RIGHT, DOWN };
        bool canGo(MazeCard::CANGO dir);
        void turnRight();
        string type;
    protected:
    private:
        void initPath();
        void setPath(string type);
        bool path[4];
};

#endif // MAZECARD_H
