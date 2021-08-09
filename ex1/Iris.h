#ifndef AP1_IRIS_H
#define AP1_IRIS_H


#include <string>
#include <vector>
#include "Classifiable.h"

class Iris : public Classifiable<Iris> {
private:
    double petalLength, petalWidth, sepalLength, sepalWidth;
    std::string type = "None";
public:
    double distance(const Iris &) const override;

    double getPetalLength() const;

    double getPetalWidth() const;

    double getSepalWidth() const;

    double getSepalLength() const;

    std::string getType() const override;

    Iris(double petalLength, double petalWidth, double sepalLength, double sepalWidth);

    Iris(double petalLength, double petalWidth, double sepalLength, double sepalWidth, std::string type);

    explicit Iris(const std::vector<std::string> &);

    Iris(Iris &&o) = default;

    Iris(const Iris &o) = default;

    Iris &operator=(const Iris &) = default;

    ~Iris() = default;
};

std::vector<Iris> toIrisVector(const std::vector<std::vector<std::string>>&);


#endif //AP1_IRIS_H
