#ifndef MAZEFIELD_H
#define MAZEFIELD_H

#include "MazeCard.h"

class MazeField
{
    public:
        MazeField(int r, int c);
        virtual ~MazeField();
        int row();
        int col();
        MazeCard getCard();
        void putCard(MazeCard c);
    protected:
    private:
        int _row;
        int _col;
        MazeCard _cardL;
};

#endif // MAZEFIELD_H
