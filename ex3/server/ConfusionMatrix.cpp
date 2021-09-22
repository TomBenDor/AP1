#include "ConfusionMatrix.h"


ConfusionMatrix::ConfusionMatrix(std::vector<std::vector<double>> entries, std::vector<std::string> types) : entries(
        std::move(entries)),
                                                                                                             types(std::move(
                                                                                                                     types)) {
}

std::string ConfusionMatrix::toString() {
    std::string matrix;
    for (int i = 0; i < types[0].size(); ++i) {
        matrix += " ";
    }
    for (const std::string &type: this->types) {
        matrix += '\t';
        matrix += type;
    }
    matrix += '\n';
    for (int i = 0; i < entries.size(); i++) {
        matrix += types[i];
        for (double d: entries[i]) {
            matrix += '\t';
            matrix += std::to_string(d);
            matrix += "%";
        }
        matrix += '\n';
    }
    return matrix;
}