#ifndef MAZEBOARD_H
#define MAZEBOARD_H

#include "GameGenerator.h"
#include "MazeCard.h"
#include "MazeField.h"
#include <vector>

class MazeBoard
{
    public:
        MazeBoard();
        MazeBoard(int n);
        virtual ~MazeBoard();
        static MazeBoard createMazeBoard(int n);
        void newGame();
        MazeField get(int r, int c);
        MazeCard getFreeCard();
        void shift(MazeField mf);
    protected:
    private:
        MazeCard _freeCard;
        MazeCard getCard(int r, int c);
        void putCard(int r, int c, MazeCard card);
        int rowLen;
        void shiftDown(int c);
        void shiftUp(int c);
        void shiftRight(int r);
        void shiftLeft(int r);
        vector<MazeField> _fields;
};

#endif // MAZEBOARD_H
