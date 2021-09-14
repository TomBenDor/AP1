#ifndef AP1_IRIS_H
#define AP1_IRIS_H


#include <string>
#include <vector>
#include "Classifiable.h"

//Iris class
class Iris : public Classifiable {
private:
    //coordinates and type
    double petalLength, petalWidth, sepalLength, sepalWidth;
    std::string type = "None";
public:
    std::vector<double> getVector() const override;

    double getPetalLength() const;

    double getPetalWidth() const;

    double getSepalWidth() const;

    double getSepalLength() const;

    std::string getType() const override;

    //Construct an iris using a vector with its coordinates
    explicit Iris(const std::vector<std::string> &);

    explicit Iris(const std::string &);

    Iris(Iris &&o) = default;

    Iris(const Iris &o) = default;

    Iris &operator=(const Iris &) = default;

    ~Iris() = default;
};

//Create a vector of irises using a matrix
std::vector<Iris> toIrisVector(const std::vector<std::vector<std::string>> &);


#endif //AP1_IRIS_H
