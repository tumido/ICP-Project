/**
 * @file MazeField.h
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Class defining the the field on the board
 */
#ifndef MAZEFIELD_H
#define MAZEFIELD_H

#include "MazeCard.h"

/// @brief Class containig the field data like card, and handles the neighborhood
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
