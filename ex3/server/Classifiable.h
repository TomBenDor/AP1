#ifndef AP1_CLASSIFIABLE_H
#define AP1_CLASSIFIABLE_H

//Classifiable interface
template<class T>
class Classifiable {
    //Euclidean distance
    virtual double euc_distance(const T &other) const = 0;

    //Manhattan distance
    virtual double man_distance(const T &other) const = 0;

    //Chebyshev distance
    virtual double che_distance(const T &other) const = 0;


    virtual std::string getType() const = 0;
};


#endif //AP1_CLASSIFIABLE_H
