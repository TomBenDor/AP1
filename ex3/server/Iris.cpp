#include "Iris.h"
#include "../utils.h"
#include <cmath>

std::string Iris::getType() const {
    if (!isClassified) {
        perror("Iris is not classified!");
    }
    return type;
}

double Iris::distance(const Iris &other) const {
    double sum = 0;
    for (int i = 0; i < coordinates.size(); i++) {
        sum += std::pow(coordinates[i] - other.coordinates[i], 2);
    }
    return std::sqrt(sum);
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