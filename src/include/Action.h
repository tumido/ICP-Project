/**
 * @file Action.h
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Defines the action done on one turn
 */
#ifndef ACTION_H
#define ACTION_H

/// @brief Defines the action done on one turn
class Action
{
    public:
        enum TYPE { MOVE_PLAYER, MOVE_CARD, TAKE_TREASURE }; /// action type
        Action(enum TYPE type, int r, int c);
        virtual ~Action();
        int row();
        int col();
        enum TYPE type();
    protected:
    private:
        int _row;
        int _col;
        enum TYPE _type;
};

#endif // ACTION_H
