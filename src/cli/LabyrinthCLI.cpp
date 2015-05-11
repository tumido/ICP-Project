#include "../../include/LabyrinthCLI.h"

LabyrinthCLI::LabyrinthCLI()
{
    game = new GameManager;
}

LabyrinthCLI::~LabyrinthCLI()
{
    delete game;
}

/**
 * Prompt help
 */
void LabyrinthCLI::print_help()
{
  cout << "Before the game starts:" << endl;
  cout << "-----------------------------------------" << endl;
  cout << setw(20) << "'set size N'" << "\tset the board size" << endl;
  cout << setw(20) << "'set treasure N'" << "\tset the treasure count" << endl;
  cout << setw(20) << "'player NAME'" << "\tadd player" << endl;
  cout << setw(20) << "'start'" << "\tstart the game" << endl;
  cout << "In-game commands:" << endl;
  cout << "-----------------------------------------" << endl;
  cout << setw(20) << "'move X Y'" << "\tmove player" << endl;
  cout << setw(20) << "'card X Y'" << "\tplace card" << endl;
  cout << setw(20) << "'restart'" << "\trestart the game" << endl;
  cout << "Misc:" << endl;
  cout << "-----------------------------------------" << endl;
  cout << setw(20) << "'load MAP'" << "\tload map" << endl;
  cout << setw(20) << "'store MAP'" << "\tstore map" << endl;
  cout << setw(20) << "'quit', 'q'" << "\texit the program gracefully" << endl;
}


void LabyrinthCLI::fail()
{
  cout << "Command not recognised" << endl;
}

void LabyrinthCLI::pregame()
{
  return;
}

void LabyrinthCLI::ingame()
{
  return;
}

void LabyrinthCLI::exec()
{
    clear_screen();
    cout << "Welcome to the Labyrinth game" << endl;
    cout << "-----------------------------------------" << endl;
    this->print_help();

    while (true)
    {
        command = readCommand();
        if (command[0] == "quit" || command[0] == "q")
            return;
        if (game->isStarted())
            this->pregame();
        else
            this->ingame();
    }
}
