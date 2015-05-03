#ifndef TREASURE_H
#define TREASURE_H


class Treasure
{
    public:
        Treasure();
        static void createSet();
        static Treasure getTreasure(int code);
    protected:
    private:
        Treasure(int code);
        int _count = 24;
};

#endif // TREASURE_H
