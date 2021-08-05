#include "string"
#include "Unclassified.h"
#ifndef AP1_CLASSIFIER_H
#define AP1_CLASSIFIER_H

template <class T>
class Classifier {
    virtual std::string classify(Unclassified<T> unclassified)=0;

};


#endif //AP1_CLASSIFIER_H
