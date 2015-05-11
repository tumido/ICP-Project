/**
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 */
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
        MazeCard *getCardP();
        void putCard(MazeCard c);
    protected:
    private:
        int _row;
        int _col;
        MazeCard _cardL;
};

#endif // MAZEFIELD_H
