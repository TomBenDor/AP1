#include "vector"
#include "string"

#ifndef TESTING_MATRIX_H
#define TESTING_MATRIX_H


class ConfusionMatrix {
private:
    std::vector<std::vector<double>> entries;
    std::vector<std::string> types;

public:
    ConfusionMatrix(std::vector<std::vector<double>> entries, std::vector<std::string> types);

    std::string toString();

};


#endif //TESTING_MATRIX_H
