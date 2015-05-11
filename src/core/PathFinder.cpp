/**
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 */
#include "../../include/PathFinder.h"
#include <iostream>

/**
 * Check whether path between current field and destination exists
 *
 * @param curr Current field
 * @param dest Destination field
 */
bool PathFinder::findPath(MazeField curr, MazeField dest, MazeBoard &board)
{
    int counter = 0;
    int added = 0;
    int limit = board.getSize() - 1;
    vector<MazeField> coordinates;
    coordinates.push_back(curr);
    while ((added >= counter || (added == 0 && counter == 0)) && (unsigned)counter < coordinates.size()) {
        curr = coordinates[counter];
        if (curr.col() == dest.col() && curr.row() == dest.row())
            return true;
        MazeCard card = curr.getCard();
        if (card.canGo(MazeCard::CANGO::UP)) {
            if (curr.col() > 0) {
                MazeField mf = board.get(curr.row(), curr.col() - 1);
                if (mf.row() > -1) {
                    MazeCard card2 = mf.getCard();
                    if (card2.canGo(MazeCard::CANGO::DOWN) && !PathFinder::containsField(mf, coordinates)) {
                        coordinates.push_back(mf);
                        added++;
                    }
                }
            }
        }
        if (card.canGo(MazeCard::CANGO::DOWN)) {
            if (curr.col() < limit) {
                MazeField mf = board.get(curr.row(), curr.col() + 1);
                if (mf.row() > -1) {
                    MazeCard card2 = mf.getCard();
                    if (card2.canGo(MazeCard::CANGO::UP) && !PathFinder::containsField(mf, coordinates)) {
                        coordinates.push_back(mf);
                        added++;
                    }
                }
            }
        }
        if (card.canGo(MazeCard::CANGO::LEFT)) {
            if (curr.row() > 0) {
                MazeField mf = board.get(curr.row() - 1, curr.col());
                if (mf.row() > -1) {
                    MazeCard card2 = mf.getCard();
                    if (card2.canGo(MazeCard::CANGO::RIGHT) && !PathFinder::containsField(mf, coordinates)) {
                        coordinates.push_back(mf);
                        added++;
                    }
                }
            }
        }
        if (card.canGo(MazeCard::CANGO::RIGHT)) {
                if (curr.row() < limit) {
                MazeField mf = board.get(curr.row() + 1, curr.col());
                if (mf.row() > -1) {
                    MazeCard card2 = mf.getCard();
                    if (card2.canGo(MazeCard::CANGO::LEFT) && !PathFinder::containsField(mf, coordinates)) {
                        coordinates.push_back(mf);
                        added++;
                    }
                }
            }
        }
        counter++;
    }
    return false;
}
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
    /*std::cout << "*** current ***" << std::endl;
    std::cout << current.getCard().getStringPath() << " ";
    std::cout << "Col: " << current.col() << "; Row: " << current.row() <<std::endl;
    std::cout << "*** next ***" << std::endl;
    std::cout << next.getCard().getStringPath() << " ";
    std::cout << "Col: " << next.col() << "; Row: " << next.row() <<std::endl;*/
    if (current.col() + 1 == next.col()) {
        return current.getCard().canGo(MazeCard::CANGO::RIGHT) &&
               next.getCard().canGo(MazeCard::CANGO::LEFT);
    } else if (current.col() - 1 == next.col()) {
        return current.getCard().canGo(MazeCard::CANGO::LEFT) &&
               next.getCard().canGo(MazeCard::CANGO::RIGHT);
    } else if (current.row() + 1 == next.row()) {
        return current.getCard().canGo(MazeCard::CANGO::UP) &&
               next.getCard().canGo(MazeCard::CANGO::DOWN);
    } else if (current.row() - 1 == next.row()) {
        return current.getCard().canGo(MazeCard::CANGO::DOWN) &&
               next.getCard().canGo(MazeCard::CANGO::UP);
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
