#ifndef AP1_IRIS_H
#define AP1_IRIS_H


#include <string>
#include "Comparable.h"

class Iris : public Comparable<Iris> {
private:
    double petalLength, petalWidth, sepalLength, sepalWidth;
public:
    double distance(Comparable<Iris>) const override;

    double getPetalLength() const;

    double getPetalWidth() const;

    double getSepalWidth() const;

    double getSepalLength() const;

    Iris(double petalLength, double petalWidth, double sepalLength, double sepalWidth);

};


#endif //AP1_IRIS_H
