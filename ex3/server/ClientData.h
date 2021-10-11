#include "KnnClassifier.h"

#ifndef TESTING_CLIENTDATA_H
#define TESTING_CLIENTDATA_H

template<class T>
class ClientData {
private:
    KnnClassifier<T> *classifier;
    std::vector<T> test;
    std::vector<std::string> classified;
public:
    explicit ClientData(KnnClassifier<T> *knnClassifier) : classifier(knnClassifier) {}

    void classify() {
        classified.clear();
        for (auto t: test) {
            classified.push_back(classifier->classify(t));
        }
    }

    KnnClassifier<T> *getClassifier() const {
        return classifier;
    }

    const std::vector<std::string> &getClassified() const {
        return classified;
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
