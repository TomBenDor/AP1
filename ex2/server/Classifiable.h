#ifndef AP1_CLASSIFIABLE_H
#define AP1_CLASSIFIABLE_H

//Classifiable interface
template<class T>
class Classifiable {
    virtual double distance(const T &other) const = 0;

    virtual std::string getType() const = 0;
};


#endif //AP1_CLASSIFIABLE_H
