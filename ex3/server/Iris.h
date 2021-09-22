#ifndef AP1_IRIS_H
#define AP1_IRIS_H


#include <string>
#include <vector>
#include "Classifiable.h"

//Iris class
class Iris : public Classifiable {
private:
    //coordinates and type
    std::vector<double> coordinates;
    std::string type = "None";
    bool isClassified;
public:
    std::vector<double> getVector() const override;

    std::string getType() const override;

    //Construct an iris using a vector with its coordinates
    explicit Iris(const std::vector<std::string> &, bool);

    explicit Iris(const Iris &, std::string);

    Iris(Iris &&o) = default;

    Iris(const Iris &o) = default;

    Iris &operator=(const Iris &) = default;

    ~Iris() = default;
};

//Create a vector of irises using a matrix
std::vector<Iris> toIrisVector(const std::vector<std::vector<std::string>> &, bool);

std::vector<Iris> stringToIrisVector(const std::string &, bool);


#endif //AP1_IRIS_H
