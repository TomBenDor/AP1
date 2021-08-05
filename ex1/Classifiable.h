#include "Comparable.h"

#ifndef AP1_CLASSIFIABLE_H
#define AP1_CLASSIFIABLE_H

template<class T>
class Classifiable {
private:
    Comparable<T> *comparable;
public:
    double distance(Classifiable<T> other);

    Comparable<T> getComparable();
};


#endif //AP1_CLASSIFIABLE_H
