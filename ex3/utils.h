#ifndef AP1_UTILS_H
#define AP1_UTILS_H

#include "vector"
#include "string"

namespace utils {
    std::vector<std::vector<std::string>> readCSV(const std::string &);

    void writeCSV(const std::string &, const std::vector<std::string> &);

    std::vector<std::string> split(const std::string &, char);

    std::string recv(int);

    void send(int, const std::string &);

    void close(int sock);
}
#endif //AP1_UTILS_H
