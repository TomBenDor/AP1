#include "Distance.h"
#include "vector"
#include <cstdio>
#include <cmath>

#ifndef CLIENT_MANHATTANDISTANCE_H
#define CLIENT_MANHATTANDISTANCE_H


template<class T>
class ManhattanDistance : public Distance<T> {
public:
    double distance(T t1, T t2) const override {
        //Get the coordinates
        std::vector<double> t1Coordinates = t1.getVector();
        std::vector<double> t2Coordinates = t2.getVector();
        if (t2Coordinates.size() != t1Coordinates.size()) {
            perror("Vector lengths have to be equal");
        }
        if (t2Coordinates.empty()) {
            perror("Vector can't be empty");
        }
        //Calculate the distance
        double res = 0;
        for (int i = 0; i < t1Coordinates.size(); i++) {
            res += std::abs(t1Coordinates.at(i) - t2Coordinates.at(i));
        }
        return res;
    }

    std::string toString() const override {
        return "MAN";
    }
};


#endif //CLIENT_MANHATTANDISTANCE_H
