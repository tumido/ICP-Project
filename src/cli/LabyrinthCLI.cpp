#include "../../include/LabyrinthCLI.h"

LabyrinthCLI::LabyrinthCLI()
{
    game = new GameManager;
    turnStatus = true;
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
  cout << "Command not recognised or is not available right now" << endl;
}

void LabyrinthCLI::pregame()
{
    if (command[0] == "start")
    {
        game->startGame();
        return;
    }
    if (command[0] == "set")
    {
        if (command.size() == 3 && command[1] == "size")
        {
            if (!game->setSize(str_to_int(command[2])))
               this->fail();
        }
        if (command.size() == 3 && command[1] == "treasure")
        {
            if (!game->setTreasureCount(str_to_int(command[2])))
                this->fail();
        }
        else
            this->fail();
        return;
    }
    if (command.size() == 2 && command[0] == "player")
        if(!game->addPlayer(command[2]))
            this->fail();
    this->fail();
    return;
}

void LabyrinthCLI::ingame()
{
    if (command[0] == "restart")
    {
        game->restartGame();
        return;
    }
    if (command[0] == "move" && command.size() == 3)
    {
        if (!turnStatus && !game->movePlayer(str_to_int(command[1]), str_to_int(command[2])))
            this->fail();
        else
            turnStatus = false;
    }
    else if (command[0] == "card" && command.size() == 3)
    {
        if (turnStatus && !game->moveCard(str_to_int(command[1]), str_to_int(command[2])))
            this->fail();
        else
            turnStatus = true;
    }
    else
        this->fail();

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
        else if (command[0] == "load" && command.size() == 2)
        {
            if (!game->load(command[1]))
                this->fail();
        }
        else if (command[0] == "save" && command.size() == 2)
        {
            if (!game->save(command[1]))
                this->fail();
        }
        else if (game->isStarted())
        {
            this->pregame();
        }
        else
            this->ingame();
    }
}
