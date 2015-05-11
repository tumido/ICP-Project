/**
 * @file LabyrinthCLI.cpp
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Main CLI class definition
 */
#include "../include/LabyrinthCLI.h"

LabyrinthCLI::LabyrinthCLI()
{
    game = new GameManager;
    board = new OutputCLI(game);
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
        if (!game->startGame())
        {
            this->fail();
            return;
        }
        board->load();
        board->draw();
        std::cout << "Let's play! The first player should place the spare card now" << endl;
        return;
    }
    if (command[0] == "set")
    {
        if (command.size() == 3 && command[1] == "size")
        {
            if (!game->setSize(io::str_to_int(command[2])))
               this->fail();
        }
        else if (command.size() == 3 && command[1] == "treasure")
        {
            if (!game->setTreasureCount(io::str_to_int(command[2])))
                this->fail();
        }
        else
            this->fail();
        return;
    }
    if (command.size() == 2 && command[0] == "player")
    {
        if(!game->addPlayer(command[1]))
            this->fail();
        return;
    }
    this->fail();
    return;
}

void LabyrinthCLI::ingame()
{
    if (command[0] == "restart")
    {
        game->restartGame();
        board->load();
        board->draw();
        return;
    }
    if (command[0] == "move" && command.size() == 3)
    {
        if (!turnStatus && !game->movePlayer(io::str_to_int(command[1]), io::str_to_int(command[2])))
            this->fail();
        else
            turnStatus = false;
    }
    else if (command[0] == "card" && command.size() == 3)
    {
        if (turnStatus && !game->moveCard(io::str_to_int(command[1]), io::str_to_int(command[2])))
            this->fail();
        else
            turnStatus = true;
    }
    else
    {
        this->fail();
        return;
    }
    io::clear_screen();
    board->draw();
    string status = turnStatus ? "Please move your figure" : "Please place a card";
    std::cout << status << endl;
    return;
}

void LabyrinthCLI::exec()
{
    io::clear_screen();
    std::cout << "Welcome to the Labyrinth game" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    this->print_help();

    while (true)
    {
        command = io::readCommand();
        io::clear_screen();
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
        else if (command[0] == "help")
            this->print_help();
        else if (!game->isStarted())
        {
            this->pregame();
        }
        else
            this->ingame();
    }
}
