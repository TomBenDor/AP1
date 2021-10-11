#include "vector"
#ifndef AP1_CLASSIFIABLE_H
#define AP1_CLASSIFIABLE_H

class Classifiable {

    virtual std::string getType() const = 0;

    virtual std::vector<double> getVector() const = 0;
};


#endif //AP1_CLASSIFIABLE_H
