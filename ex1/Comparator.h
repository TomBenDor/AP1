#include "Iris.h"

#ifndef AP1_COMPARATOR_H
#define AP1_COMPARATOR_H


class Comparator {
    Iris compareTo;
public:
    bool operator()(const Iris &iris1, const Iris &iris2);

    explicit Comparator(Iris compareTo);
};


#endif //AP1_COMPARATOR_H
