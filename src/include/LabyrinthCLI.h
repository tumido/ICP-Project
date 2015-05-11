/**
 * @file LabyrinthCLI.h
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Main CLI class declaration
 */
#ifndef LABYRINTHCLI_H
#define LABYRINTHCLI_H

#include <iostream>
#include <sstream>
#include <iomanip>

#include "MazeCard.h"
#include "GameManager.h"
#include "Player.h"
#include "CANGO.h"
#include "DEFAULT_VALUES.h"
#include "io.h"
#include "OutputCLI.h"

/// @brief Class for game in CLI interface
class LabyrinthCLI
{

public:
    LabyrinthCLI();
    virtual ~LabyrinthCLI();
    void exec();
private:
    void fail();
    void print_help();
    void pregame();
    void ingame();
    GameManager * game;
    vector<std::string> command;
    bool turnStatus;
    OutputCLI * board;
};
#endif
