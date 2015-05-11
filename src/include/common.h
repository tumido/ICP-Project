/**
 * @file common.h
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Common functions used by core
 */
#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

#endif // COMMON_H_INCLUDED
