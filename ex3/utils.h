#ifndef AP1_UTILS_H
#define AP1_UTILS_H

#include "vector"
#include "string"

std::vector<std::vector<std::string>> readCSV(const std::string &);

void writeCSV(const std::string &, const std::vector<std::string> &);

std::vector<std::string> split(const std::string &, char);


#endif //AP1_UTILS_H
