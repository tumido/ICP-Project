#ifndef MAZEBOARD_H
#define MAZEBOARD_H

#include <algorithm>
#include <vector>

#include "GameGenerator.h"
#include "MazeCard.h"
#include "MazeField.h"

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
        void placeTreasures(vector<int> treasure);
    protected:
    private:
        MazeCard _freeCard;
        MazeCard getCard(int r, int c);
        void placeTreasure(int r, int c, int id);
        void putCard(int r, int c, MazeCard card);
        int rowLen;
        void shiftDown(int c);
        void shiftUp(int c);
        void shiftRight(int r);
        void shiftLeft(int r);
        vector<MazeField> _fields;
};

#endif // MAZEBOARD_H
