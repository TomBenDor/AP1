#include "KnnClassifier.h"

#ifndef TESTING_CLIENTDATA_H
#define TESTING_CLIENTDATA_H

template<class T>
class ClientData {
private:
    KnnClassifier<T> *classifier;
    std::vector<T> test;
public:
    explicit ClientData(KnnClassifier<T> *knnClassifier) : classifier(knnClassifier) {}

    KnnClassifier<T> *getClassifier() const {
        return classifier;
    }

    void setTrain(const std::vector<T> &v) {
        classifier->setData(v);
    }

    const std::vector<T> &getTest() const {
        return test;
    }

    void setTest(const std::vector<T> &v) {
        this->test = v;
    }
};


#endif //TESTING_CLIENTDATA_H
