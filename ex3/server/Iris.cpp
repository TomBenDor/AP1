#include "Iris.h"
#include "../utils.h"

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

std::vector<double> Iris::getVector() const {
    std::vector<double> res;
    res.push_back(this->sepalLength);
    res.push_back(this->sepalWidth);
    res.push_back(this->petalWidth);
    res.push_back(this->petalLength);
    return res;
}

Iris::Iris(const std::vector<std::string> &v) :
        sepalLength(std::stod(v[0])),
        sepalWidth(std::stod(v[1])),
        petalWidth(std::stod(v[2])),
        petalLength(std::stod(v[3])) {
    if (v.size() == 5) {
        this->type = v.at(4);
    }

}

Iris::Iris(const std::string &s) : Iris(utils::split(s, ' ')) {

}

std::vector<Iris> toIrisVector(const std::vector<std::vector<std::string>> &data) {
    std::vector<Iris> result;
    for (const auto &v: data) {
        Iris iris(v);
        result.push_back(iris);
    }
    return result;
}