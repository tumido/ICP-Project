#ifndef ACTION_H
#define ACTION_H


class Action
{
    public:
        enum TYPE { MOVE_PLAYER, MOVE_CARD };
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