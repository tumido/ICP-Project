#ifndef IO_H
#define IO_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include<vector>

#define RETRY_LIMIT 100

namespace io{
void clear_screen();
int str_to_int(const std::string &str);
std::vector<std::string> readCommand();
}
#endif // IO_H
