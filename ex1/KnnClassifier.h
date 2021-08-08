#include "Iris.h"
#include "vector"
#include "string"

#ifndef AP1_KNNCLASSIFIER_H
#define AP1_KNNCLASSIFIER_H

class KnnClassifier {
private:
    std::vector<Iris> data;
    int k;
public:
    explicit KnnClassifier(const std::vector<Iris> &data,int k);

    std::string classify(Iris &unclassified);
};


#endif //AP1_KNNCLASSIFIER_H
