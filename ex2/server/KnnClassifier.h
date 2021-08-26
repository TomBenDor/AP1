#include <algorithm>
#include "Iris.h"
#include "vector"
#include "string"
#include "map"
#include "type_traits"
#include "Classifier.h"

#ifndef AP1_KNNCLASSIFIER_H
#define AP1_KNNCLASSIFIER_H

//KnnClassifier
template<class T>
class KnnClassifier : public Classifier<T> {
private:
    //The list of the classifiables to use in the algorithm
    std::vector<T> data;
    int k;

    //The comparator class
    class Comparator {
        //A classifiable that the class
        T compareTo;
    public:
        //Compare using distances from the classifiable
        bool operator()(const T &t1, const T &t2) {
            return compareTo.distance(t1) < compareTo.distance(t2);
        }

        explicit Comparator(T t) : compareTo(t) {
        }
    };

public:
    explicit KnnClassifier(const std::vector<T> &data, int k) : k(k) {
        for (auto object: data) {
            this->data.push_back(object);
        }
    }

    //Classify an unclassified
    std::string classify(T &unclassified) {
        //Sort the vector and get the first k elements
        std::sort(data.begin(), data.end(), Comparator(std::move(unclassified)));
        auto start = data.begin();
        auto end = data.begin() + k;
        std::vector<T> knn;
        for (auto i = start; i != end; i++) {
            knn.push_back(*i);
        }
        //Count the appearances of each type
        std::map<std::string, int> predictions;
        for (auto object: knn) {
            if (predictions.count(object.getType()) == 0) {
                predictions[object.getType()] = 0;
            }
            predictions[object.getType()]++;

        }
        //Return the type with the max amount of appearances
        int max = 0;
        std::string maxType;

        for (const auto &pair: predictions) {

            if (max < pair.second) {
                maxType = pair.first;
                max = pair.second;
            }
        }

        return maxType;
    }

    ~KnnClassifier() = default;

    KnnClassifier(KnnClassifier &&o) noexcept = default;

    KnnClassifier(const KnnClassifier &o) = default;

    KnnClassifier &operator=(const KnnClassifier &) = default;
};


#endif //AP1_KNNCLASSIFIER_H
