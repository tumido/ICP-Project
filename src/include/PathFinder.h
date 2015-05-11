/**
 * @file PathFinder.h
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Class containing the logic of the path finding for the player
 */
#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "MazeBoard.h"

#include <vector>

/// @brief PathFinder is class that handles the logic of the path finding
class PathFinder
{
    public:
        static bool findPath(MazeField curr, MazeField dest, MazeBoard &board);
        static vector<MazeField> possibleMoves(MazeField current,
                                               MazeBoard board);
        static bool containsField(MazeField field,
                                  vector<MazeField> fields);
    protected:
    private:
        static bool fieldsConnected(MazeField current,
                                    MazeField next);
        static vector<MazeField> getNear(MazeField field,
                                         MazeBoard board);
};

#endif // PATHFINDER_H
