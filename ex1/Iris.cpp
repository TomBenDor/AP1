#include "Iris.h"
#include <cmath>

double Iris::getPetalLength() const {
    return petalLength;
}

double Iris::getPetalWidth() const {
    return petalLength;
}

double Iris::getSepalLength() const {
    return sepalLength;
}

double Iris::getSepalWidth() const {
    return sepalWidth;
}


Iris::Iris(double petalLength, double petalWidth, double sepalLength, double sepalWidth) : petalLength(petalLength),
                                                                                           petalWidth(petalWidth),
                                                                                           sepalLength(sepalLength),
                                                                                           sepalWidth(sepalWidth) {
}

double Iris::distance(Comparable<Iris> other) const {
    return std::sqrt(std::pow(this->sepalWidth - other.getType().getSepalWidth(), 2)
                     + std::pow(this->sepalLength - other.getType().getSepalLength(), 2) +
                     std::pow(this->petalLength - other.getType().getPetalLength(), 2)
                     + std::pow(this->petalWidth - other.getType().getPetalWidth(), 2));;
}

