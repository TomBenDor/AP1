#include <fstream>
#include <iostream>
#include <sstream>
#include "utils.h"


std::vector<std::vector<std::string>> readCSV(const std::string& path) {
    std::ifstream fin(path);

    if (!fin.is_open()) throw std::runtime_error("Could not open file");

    std::vector<std::vector<std::string>> data;
    std::string line, cell;

    while (fin.good()) {
        std::getline(fin, line);
        std::stringstream ss(line);

        std::vector<std::string> row;
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }

    return data;
}
