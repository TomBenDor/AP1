
#include "Classifiable.h"

template<class T>
Comparable<T> Classifiable<T>::getComparable() {
    return this->comparable;
}

template<class T>
double Classifiable<T>::distance(Classifiable<T> other) {
    return (this->comparable).distance(other.getComparable());
}
