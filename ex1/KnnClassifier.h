#include "Classifier.h"
#include "Classified.h"
#include "vector"
#include "string"

#ifndef AP1_KNNCLASSIFIER_H
#define AP1_KNNCLASSIFIER_H

template<class T>
class KnnClassifier : public Classifier<T> {
private:
    std::vector<Classified<T>> data;
public:
    std::string classify(Unclassified<T>) override;
};


#endif //AP1_KNNCLASSIFIER_H
