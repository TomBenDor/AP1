#include "Comparator.h"


bool Comparator::operator()(const Iris &iris1, const Iris &iris2) {
    return iris1.distance(compareTo) < iris2.distance(compareTo);
}

Comparator::Comparator(Iris i) : compareTo(i) {
}
