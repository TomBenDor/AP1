#include "Iris.h"
#include "vector"
#include "../utils.h"

std::string Iris::getType() const {
    if (!isClassified) {
        perror("Iris is not classified!");
    }
    return type;
}


std::vector<double> Iris::getVector() const {
    return this->coordinates;
}


Iris::Iris(const std::vector<std::string> &v, bool isClassified) : isClassified(isClassified) {
    if (isClassified) {
        for (int i = 0; i < v.size() - 1; i++) {
            coordinates.push_back(std::stod(v[i]));
        }
        type = v[v.size() - 1];
    } else {
        for (const auto &i: v) {
            coordinates.push_back(std::stod(i));
        }
    }
}

std::vector<Iris> toIrisVector(const std::vector<std::vector<std::string>> &data, bool isClassified) {
    std::vector<Iris> result;
    for (const auto &v: data) {
        Iris iris(v, isClassified);
        result.push_back(iris);
    }
    return result;
}

std::vector<Iris> stringToIrisVector(const std::string &encoding, bool isClassified) {
    std::vector<std::string> irises = utils::split(encoding, '\n');
    std::vector<std::vector<std::string>> coordinates;
    for (const std::string &stringCoordinates: irises) {
        std::vector<std::string> irisCoordinates = utils::split(stringCoordinates, ' ');
        coordinates.push_back(irisCoordinates);
    }
    return toIrisVector(coordinates, isClassified);
}
