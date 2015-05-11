/**
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 */
#ifndef GAMEGENERATOR_H
#define GAMEGENERATOR_H

#include "MazeCard.h"
#include <random>
#include <vector>

class GameGenerator
{
    public:
        GameGenerator();
        virtual ~GameGenerator();
        static MazeCard generateCard();
        static vector<MazeCard> generateCards(int n);
    protected:
    private:
};

#endif // GAMEGENERATOR_H
