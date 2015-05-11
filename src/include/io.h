/**
 * @file io.h
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Adds IO namespace for CLI front-end
 */
#ifndef IO_H
#define IO_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include<vector>

#define RETRY_LIMIT 100

/// Input Output namespace for CLI variant
namespace io{
    void clear_screen();
    int str_to_int(const std::string &str);
    std::vector<std::string> readCommand();
}
#endif // IO_H
