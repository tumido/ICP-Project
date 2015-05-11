#include "../../include/io.h"

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
vector<string> readCommand()
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
