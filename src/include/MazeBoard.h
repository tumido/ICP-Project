/**
 * @file MazeBoard.h
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Class defining the board of the game
 */
#ifndef MAZEBOARD_H
#define MAZEBOARD_H

#include <algorithm>
#include <vector>
#include <sstream>

#include "GameGenerator.h"
#include "MazeCard.h"
#include "MazeField.h"

/// @brief Class definig the board layout and content
class MazeBoard
{
    public:
        MazeBoard();
        MazeBoard(int n);
        virtual ~MazeBoard();
        static MazeBoard createMazeBoard(int n);
        void newGame();
        MazeField get(int r, int c);
        MazeField *getP(int r, int c);
        MazeCard getFreeCard();
        bool shift(MazeField mf, bool undo = false);
        void placeTreasures(vector<int> treasure);
        void turnFreeCard();
        string toString();
        void setFreeCard(MazeCard card);
        void putCard(int r, int c, MazeCard card);
        int getSize();
    protected:
    private:
        MazeCard _freeCard;
        MazeCard getCard(int r, int c);
        MazeCard *getCardP(int r, int c);
        void placeTreasure(int r, int c, int id);
        void defaultCards();
        int rowLen;
        void shiftDown(int c);
        void shiftUp(int c);
        void shiftRight(int r);
        void shiftLeft(int r);
        MazeField _previous = MazeField(-1,-1);
        bool canPlay(MazeField mf);
        vector<MazeField> _fields;
};

#endif // MAZEBOARD_H
