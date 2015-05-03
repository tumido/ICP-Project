#ifndef CARDPACK_H
#define CARDPACK_H

#include "TreasureCard.h"

class CardPack
{
    public:
        CardPack(int maxSize, int initSize);
        virtual ~CardPack();
        TreasureCard popCard();
        int size();
        void shuffle();
    protected:
    private:
};

#endif // CARDPACK_H
