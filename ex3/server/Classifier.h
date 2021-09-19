#include "string"
#include "Classifiable.h"

#ifndef AP1_CLASSIFIER_H
#define AP1_CLASSIFIER_H

template<class T>
class Classifier {
    //Assert that the generic value is a classifiable
    static_assert(std::is_base_of<Classifiable, T>::value, "T must be subclass of Classifiable!");
public:
    virtual std::string classify(T &unclassified) = 0;

    virtual std::string toString() const = 0;

    virtual ~Classifier() = default;
};


#endif //AP1_CLASSIFIER_H
