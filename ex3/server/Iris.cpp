#include "Iris.h"
#include "stdexcept"
#include <utility>
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

Iris::Iris(const Iris &unclassified, std::string classification) : coordinates(unclassified.getVector()),
                                                                   type(std::move(classification)),
                                                                   isClassified(true) {}


std::vector<Iris> toIrisVector(const std::vector<std::vector<std::string>> &data, bool isClassified) {
    std::vector<Iris> result;
    for (const auto &v: data) {
        Iris iris(v, isClassified);
        result.push_back(iris);
    }
    return result;
}

std::vector<Iris> stringToIrisVector(const std::string &encoding, bool isClassified) {
    std::vector<std::string> irisesEncodings = utils::split(encoding, '\n');
    std::vector<Iris> irises;
    for (const std::string &coordinatesEncoding: irisesEncodings) {
        std::vector<std::string> coordinates = utils::split(coordinatesEncoding, ',');
        if (coordinates.size() < 2) {
            throw std::invalid_argument("Iris should have at least one coordinate");
        }
        irises.emplace_back(coordinates, isClassified);
    }
    return irises;
}
