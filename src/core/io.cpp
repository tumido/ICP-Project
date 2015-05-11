/**
 * @file io.cpp
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Adds IO namespace for CLI front-end
 */
#include "../include/io.h"

using namespace std;


/**
 * @brief Clears the screen
 */
void io::clear_screen()
{
  cout << string( 100, '\n' );
}

/**
 * @brief Simple string to integer converter
 *
 * @param str string to convert
 */
int io::str_to_int(const string &str)
{
  stringstream istrm(str);
  int value;
  istrm >> value;
  return value;
}

/**
 * @brief Split the user's input into words using getline
 */
vector<string> io::readCommand()
{
    int retry = 0;
    string line, word;
    vector<string> com;
    while (com.size() == 0 && retry < RETRY_LIMIT)
    {
        cout << ": ";
        getline(cin, line);
        istringstream is(line);
        while (getline(is, word, ' '))
            com.push_back(word);
        retry++;
    }
    return com;
}
