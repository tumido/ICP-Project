#include "../../include/common.h"

/**
 * Splits string by specified delimiter
 *
 * @param s String to split
 * @param delim String delimiter
 * @param elems Vector to copy to
 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

/**
 * Splits string by specified delimiter
 *
 * @param s String to split
 * @param delim String delimiter
 */
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
