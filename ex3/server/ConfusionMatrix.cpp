#include "ConfusionMatrix.h"

ConfusionMatrix::ConfusionMatrix(std::vector<std::vector<std::string>> entries, std::vector<std::string> types) :
        entries(std::move(entries)), types(std::move(types)) {
}

std::string ConfusionMatrix::toString() {
    std::string matrix;
    int maxLen = 0;
    //Get the max length of a cell in the matrix
    for (const auto &i: entries) {
        for (const auto &j: i) {
            if (j.size() + 1 > maxLen) {
                maxLen = 1 + j.size();
            }
        }
    }
    for (const auto &i: types) {
        if (i.size() > maxLen) {
            maxLen = i.size();
        }
    }
    for (int i = 0; i < maxLen; ++i) {
        matrix += " ";
    }
    //Add all types to the first row of the matrix
    for (const std::string &type: this->types) {
        matrix += separator;
        matrix += type;
        for (int j = type.size(); j < maxLen; j++) {
            matrix += ' ';
        }
    }
    //Add all lines
    matrix += '\n';
    for (int i = 0; i < entries.size(); i++) {
        //Add the type name
        matrix += types[i];
        //Add spaces to match the max length
        for (int j = types[i].size(); j < maxLen; j++) {
            matrix += ' ';
        }
        //Add percentage data to the rows
        for (const std::string &d: entries[i]) {
            matrix += separator;
            matrix += d;
            matrix += "%";
            for (int j = d.size() + 1; j < maxLen; j++) {
                matrix += ' ';
            }
        }
        matrix += '\n';
    }
    matrix.pop_back();
    return matrix;
}