#include "string"

#ifndef CLIENT_DISTANCE_H
#define CLIENT_DISTANCE_H

template<class T>
class Distance {
    static_assert(std::is_base_of<Classifiable, T>::value, "T must be subclass of Classifiable!");
public:
    virtual double distance(T t1, T t2) const = 0;

    virtual std::string toString() const = 0;
};


#endif //CLIENT_DISTANCE_H
