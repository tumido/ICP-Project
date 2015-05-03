#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "MazeBoard.h"

#include <vector>

class PathFinder
{
    public:
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
