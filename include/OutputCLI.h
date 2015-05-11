#ifndef OUTPUTCLI_H
#define OUTPUTCLI_H

#include "GameManager.h"

#include <iostream>

class OutputCLI
{
    public:
        OutputCLI(GameManager *manager);
        virtual ~OutputCLI();
        void load();
        void draw();
    protected:
    private:
        GameManager *game = NULL;
        void cardToBuffer(MazeField mf);
        char *cardString(MazeCard mc);
        void prep();
        void putPlayers();
        char *buffer = NULL;
};

#endif // OUTPUTCLI_H
