#include <algorithm>
#include "Iris.h"
#include "vector"
#include "string"
#include "map"
#include "type_traits"

#ifndef AP1_KNNCLASSIFIER_H
#define AP1_KNNCLASSIFIER_H
template<class T>
class KnnClassifier {
    static_assert(std::is_base_of<Classifiable<T>, T>::value, "T must be subclass of Classifiable!");
private:
    std::vector<T> data;
    int k;
    //The comparator class
    class Comparator {
        T compareTo;
    public:
        bool operator()(const T &t1, const T &t2){
            return compareTo.distance(t1)<compareTo.distance(t2);
        }

        explicit Comparator(T t): compareTo(t){
        }
    };
public:
    explicit KnnClassifier(const std::vector<T> &data, int k) : k(k) {
        for (auto object: data) {
            this->data.push_back(object);
        }
    }

    std::string classify(T &unclassified) {
        std::sort(data.begin(), data.end(), Comparator(std::move(unclassified)));
        auto start = data.begin();
        auto end = data.begin() + k;
        std::vector<T> knn;
        for (auto i = start; i != end; i++) {
            knn.push_back(*i);
        }

        std::map<std::string, int> predictions;
        for (auto object:knn) {
            if (predictions.count(object.getType()) == 0) {
                predictions[object.getType()] = 0;
            }
            predictions[object.getType()]++;

        }

        int max = 0;
        std::string maxType;

        for (const auto &pair : predictions) {

            if (max < pair.second) {
                maxType = pair.first;
                max = pair.second;
            }
        }

        return maxType;
    }
};


#endif //AP1_KNNCLASSIFIER_H
