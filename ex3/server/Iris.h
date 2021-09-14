#ifndef AP1_IRIS_H
#define AP1_IRIS_H


#include <string>
#include <vector>
#include "Classifiable.h"

//Iris class
class Iris : public Classifiable<Iris> {
private:
    //coordinates and type
    std::vector<double> coordinates;
    std::string type = "None";
    bool isClassified;
public:
    double distance(const Iris &) const override;

    std::string getType() const override;

    //Construct an iris using a vector with its coordinates
    explicit Iris(const std::vector<std::string> &, bool);

    Iris(Iris &&o) = default;

    Iris(const Iris &o) = default;

    Iris &operator=(const Iris &) = default;

    ~Iris() = default;
};

//Create a vector of irises using a matrix
std::vector<Iris> toIrisVector(const std::vector<std::vector<std::string>> &, bool);


#endif //AP1_IRIS_H
