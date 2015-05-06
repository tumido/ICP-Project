#include <iostream>
#include <sstream>
#include <iomanip>
#include "../include/GameManager.h"

using namespace std;

/* Clear screen function in CLI */
void clear_screen()
{
  cout << string( 100, '\n' );
}

vector<string> command()
{
  string line, word;
  vector<string> com;
  cout << ": ";
  getline(cin, line);
  istringstream is(line);
  while (getline(is, word, ' ')) {com.push_back(word); }
  return com;
}
void print_help()
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
  cout << "Misc:" << endl;
  cout << "-----------------------------------------" << endl;
  cout << setw(20) << "'load MAP'" << "\tload map" << endl;
  cout << setw(20) << "'store MAP'" << "\tstore map" << endl;
  cout << setw(20) << "'quit'" << "\texit the program gracefully" << endl;
}

void fail()
{
  cout << "Command not recognised" << endl;
}

bool execute()
{
  vector<string> com = command();
  GameManager game;
  while (com.size() == 0) com = command();
  clear_screen();
  if (com[0] == "help")
    print_help();
  else if (com[0] == "quit" || com[0] == "q")
    return false;
  else if (com[0] == "set" && com.size() == 3)
  {
    stringstream is(com[2]);
    int value;
    is >> value;
    if (com[1] == "treasure")
      game.setTreasureCount(value);
    else if (com[1] == "size")
      game.setSize(value);
    else
      fail();
  }
  else
    fail()
  return true;
}

int main()
{
  clear_screen();
  cout << "Welcome to the Labyrinth game" << endl;
  cout << "-----------------------------------------" << endl;
  cout << "Type \"help\" for more information" << endl;
  while(execute()) {}
  return EXIT_SUCCESS;
}
