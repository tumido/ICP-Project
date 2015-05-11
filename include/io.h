#ifndef IO_H
#define IO_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include<vector>

#define RETRY_LIMIT 100

using namespace std;
void clear_screen();
bool check(vector<string> & com, const string value, int index, unsigned long count);
int str_to_int(const string &str);
vector<string> readCommand();
#endif // IO_H
