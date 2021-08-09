#include "Iris.h"
#include <cmath>

double Iris::getPetalLength() const {
    return petalLength;
}

double Iris::getPetalWidth() const {
    return petalWidth;
}

double Iris::getSepalLength() const {
    return sepalLength;
}

double Iris::getSepalWidth() const {
    return sepalWidth;
}

std::string Iris::getType() const {
    return type;
}

Iris::Iris(double petalLength, double petalWidth, double sepalLength, double sepalWidth) : petalLength(petalLength),
                                                                                           petalWidth(petalWidth),
                                                                                           sepalLength(sepalLength),
                                                                                           sepalWidth(sepalWidth) {
}

Iris::Iris(double petalLength, double petalWidth, double sepalLength, double sepalWidth, std::string type)
        : petalLength(petalLength), petalWidth(petalWidth), sepalLength(sepalLength), sepalWidth(sepalWidth),
          type(std::move(type)) {}

double Iris::distance(const Iris &other) const {
    return std::sqrt(std::pow(this->sepalWidth - other.getSepalWidth(), 2)
                     + std::pow(this->sepalLength - other.getSepalLength(), 2) +
                     std::pow(this->petalLength - other.getPetalLength(), 2)
                     + std::pow(this->petalWidth - other.getPetalWidth(), 2));
}

Iris::Iris(const std::vector<std::string> &v) :
        sepalLength(std::stod(v.at(0))),
        sepalWidth(std::stod(v.at(1))),
        petalWidth(std::stod(v.at(2))),
        petalLength(std::stod(v.at(3))) {
    if (v.size() == 5) {
        this->type = v.at(4);
    }

}

std::vector<Iris> toIrisVector(const std::vector<std::vector<std::string>> &data) {
    std::vector<Iris> result;
    for (const auto &v:data) {
        Iris iris(v);
        result.push_back(iris);
    }
    return result;
}