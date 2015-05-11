/**
 * @file GameGenerator.h
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Generates map for new game
 */
#ifndef GAMEGENERATOR_H
#define GAMEGENERATOR_H

#include "MazeCard.h"
#include <random>
#include <vector>

/// @brief Map generator, randomizing setting of new map
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
