#include "Distance.h"
#include "vector"
#include <cstdio>
#include <cmath>

#ifndef CLIENT_CHEBYSHEVDISTANCE_H
#define CLIENT_CHEBYSHEVDISTANCE_H

template<class T>
class ChebyshevDistance : public Distance<T> {
public:
    double distance(T t1, T t2) const override {
        //Get coordinates
        std::vector<double> t1Coordinates = t1.getVector();
        std::vector<double> t2Coordinates = t2.getVector();
        if (t2Coordinates.size() != t1Coordinates.size()) {
            perror("Vector lengths have to be equal");
        }
        if (t2Coordinates.empty()) {
            perror("Vector can't be empty");
        }
        //Calculate the distance
        double res = std::abs(t1Coordinates.at(0) - t2Coordinates.at(0));
        for (int i = 1; i < t1Coordinates.size(); i++) {
            double cur = std::abs(t1Coordinates.at(i) - t2Coordinates.at(i));
            if (cur > res) {
                res = cur;
            }
        }
        return res;
    }

    std::string toString() const override {
        return "CHE";
    }

};


#endif //CLIENT_CHEBYSHEVDISTANCE_H
