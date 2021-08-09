#ifndef AP1_UTILS_H
#define AP1_UTILS_H

#include "vector"
#include "string"

std::vector<std::vector<std::string>> readCSV(const std::string&);
void writeCSV(const std::string&, const std::vector<std::string>&);


#endif //AP1_UTILS_H
