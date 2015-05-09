#include "../../include/PathFinder.h"

/**
 * Returns vector of all possible moves for the current player
 *
 * @param field Current field
 * @param board Game board
 */
vector<MazeField> PathFinder::possibleMoves(MazeField field,
                                            MazeBoard board)
{
    vector<MazeField> ret;
    vector<MazeField> stackField;
    stackField.push_back(field);

    while (stackField.size() > 0) {
        MazeField curr = stackField.back();
        stackField.pop_back();
        if (!(PathFinder::containsField(curr, ret) ||
            PathFinder::containsField(curr, stackField))) {
            ret.push_back(curr);
            auto near = PathFinder::getNear(field, board);
            for (unsigned int i = 0; i < near.size(); i++) {
                if (PathFinder::fieldsConnected(curr, near[i]) &&
                    !PathFinder::containsField(near[i], ret)) {
                    stackField.push_back(near[i]);
                }
            }
        }
    }
    return ret;
}

/**
 * Checks whether cards are directly connected to each other
 *
 * @param current Field no.1
 * @param next Field no.2
 */
bool PathFinder::fieldsConnected(MazeField current,
                                 MazeField next)
{
    if (current.col() + 1 == next.col()) {
        return current.getCard().canGo(MazeCard::CANGO::LEFT) &&
               next.getCard().canGo(MazeCard::CANGO::RIGHT);
    } else if (current.col() - 1 == next.col()) {
        return current.getCard().canGo(MazeCard::CANGO::RIGHT) &&
               next.getCard().canGo(MazeCard::CANGO::LEFT);
    } else if (current.row() + 1 == next.row()) {
        return current.getCard().canGo(MazeCard::CANGO::DOWN) &&
               next.getCard().canGo(MazeCard::CANGO::UP);
    } else if (current.row() - 1 == next.row()) {
        return current.getCard().canGo(MazeCard::CANGO::UP) &&
               next.getCard().canGo(MazeCard::CANGO::DOWN);
    } else {
        return false;
    }
}

/**
 * Checks whether the field is contained in the vector
 *
 * @param field Current field
 * @param fields Vector of fields
 */
bool PathFinder::containsField(MazeField field,
                               vector<MazeField> fields)
{
    for (unsigned int i = 0; i < fields.size(); i++) {
        if (fields[i].col() == field.col() &&
            fields[i].row() == field.row()) {
            return true;
        }
    }
    return false;
}

/**
 * Returns vector of all fields, that are next to the current one
 *
 * @param field Current field
 * @param board Game board
 */
vector<MazeField> PathFinder::getNear(MazeField field,
                                      MazeBoard board)
{
    vector<MazeField> nearby;
    MazeField curr = board.get(field.row() - 1, field.col());
    if (curr.row() > -1)
        nearby.push_back(curr);

    curr = board.get(field.row() + 1, field.col());
    if (curr.row() > -1)
        nearby.push_back(curr);

    curr = board.get(field.row(), field.col() - 1);
    if (curr.row() > -1)
        nearby.push_back(curr);

    curr = board.get(field.row(), field.col() + 1);
    if (curr.row() > -1)
        nearby.push_back(curr);

    return nearby;
}
