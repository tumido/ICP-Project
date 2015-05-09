#include <iostream>
#include <sstream>
#include <iomanip>
#include "../include/GameManager.h"

#define RETRY_LIMIT 100

using namespace std;

/**
 * Clears the screen
 */
void clear_screen()
{
  cout << string( 100, '\n' );
}

/**
 * Check if the command matches given string on desired index and has all arguments
 *
 * @param com Command vector containing user's input split by words
 * @param value Matching pattern
 * @param index Which member of vector the check is done against
 * @param count Number of word in command (how the command should be long)
 */
bool check(vector<string> & com, const string value, int index, unsigned long count)
{
  return com[index] == value && com.size() == count;
}

/**
 * Simple string to integer converter
 *
 * @param str string to convert
 */
int str_to_int(const string &str)
{
  stringstream istrm(str);
  int value;
  istrm >> value;
  return value;
}

/**
 * Split the user's input into words using getline
 */
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

/**
 * Prompt help
 */
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
  cout << setw(20) << "'restart'" << "\trestart the game" << endl;
  cout << "Misc:" << endl;
  cout << "-----------------------------------------" << endl;
  cout << setw(20) << "'load MAP'" << "\tload map" << endl;
  cout << setw(20) << "'store MAP'" << "\tstore map" << endl;
  cout << setw(20) << "'quit', 'q'" << "\texit the program gracefully" << endl;
}

/**
 * Why not to tell the user that his command is simply wrong...
 */
void fail()
{
  cout << "Command not recognised" << endl;
}

/**
 * Pre-game coommand parser, set's the environment before the game is launched
 * @param game GameManager instance reference
 * @param com User's input
 * @param started determine if the game is already running
 */
bool pregame(GameManager &game, vector<string> &com, bool &started)
{
  if (check(com, "quit", 0, 1) || check(com, "q", 0, 1))
    return false;
  else if (check(com, "set", 0, 3))
  {
    if (check(com, "treasure", 1, 3))
      game.setTreasureCount(str_to_int(com[2]));
    else if (check(com, "size", 1, 3))
      game.setSize(str_to_int(com[2]));
    else
      fail();
  }
  else if (check(com, "player", 0, 2))
  {
    if (!game.addPlayer(com[1]))
    {cout << "failed to add player"; return false;}
  }
  else if (check(com, "start", 0, 1))
  {
    game.startGame();
    started = true;
  }
  else
    fail();
  return true;
}

/**
 * In-game coommand parser. Let's play!
 * @param game GameManager instance reference
 * @param com User's input
 */
bool ingame(GameManager &game, vector<string> &com)
{
  if (check(com, "quit", 0, 1) || check(com, "q", 0, 1))
    return false;
  else if (check(com, "move", 0, 3))
    game.movePlayer(str_to_int(com[1]), str_to_int(com[2]));
  else if (check(com, "card", 0, 3))
    game.moveCard(str_to_int(com[1]), str_to_int(com[2]));
  else
    fail();
  return true;
}

/**
 * Runs the game, wrapper above pregame and ingame functions
 * @param game GameManager instance reference
 * @param started true if the game is already running
 */
bool execute(GameManager &game, bool &started)
{
  vector<string> com = command();
  int retry = 0; // limit to stop the execution in case of e.g CTRL+D
  while (com.size() == 0 && retry < RETRY_LIMIT) {com = command(); retry++;}
  if (retry >= RETRY_LIMIT) return false;
  clear_screen();
  print_help();
  if (!started)
    return pregame(game, com, started);
  else
    return ingame(game, com);
}

int main()
{
  clear_screen();
  cout << "Welcome to the Labyrinth game" << endl;
  cout << "-----------------------------------------" << endl;
  print_help();
  bool started = false;
  GameManager game;
  while(execute(game, started)) {}
  return EXIT_SUCCESS;
}
