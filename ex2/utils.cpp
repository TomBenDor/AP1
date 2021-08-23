#include <fstream>
#include <sstream>
#include "utils.h"

//Read a csv file and return a matrix of its lines
std::vector<std::vector<std::string>> readCSV(const std::string &path) {
    std::ifstream fin(path);

    if (!fin.is_open()) throw std::runtime_error("Could not open file");

    std::vector<std::vector<std::string>> data;
    std::string line;

    while (fin.good()) {
        std::getline(fin, line);
        std::stringstream ss(line);

        std::vector<std::string> row = split(line, ',');
        if (!row.empty())
            data.push_back(row);
    }

    return data;
}

//Write to a csv file
void writeCSV(const std::string &path, const std::vector<std::string> &data) {
    std::ofstream fout(path);

    for (const std::string &line:data) {
        fout << line << std::endl;
    }
}

std::vector<std::string> split(const std::string &s, const char c) {
    std::stringstream ss(s);
    std::string cell;

    std::vector<std::string> v;
    while (std::getline(ss, cell, c)) {
        v.push_back(cell);
    }

    return v;
}