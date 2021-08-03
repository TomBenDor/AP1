#ifndef AP1_IRIS_H
#define AP1_IRIS_H


#include <string>

class Iris {
private:
    double petalLength, petalWidth, sepalLength, sepalWidth;

public:

//    virtual double distance(const Iris &other) const;
//    double distance(Classifiable<Iris> *other) override;
    double distance(Iris &other) const;

    double getPetalLength() const;

    double getPetalWidth() const;

    double getSepalWidth() const;

    double getSepalLength() const;


    Iris(double petalLength, double petalWidth, double sepalLength, double sepalWidth);

};


#endif //AP1_IRIS_H
