#include <algorithm>
#include "Iris.h"
#include "vector"
#include "string"
#include "map"
#include "type_traits"
#include "metrics/Distance.h"
#include "string"
#include "metrics/EuclideanDistance.h"

#ifndef AP1_KNNCLASSIFIER_H
#define AP1_KNNCLASSIFIER_H

//KnnClassifier
template<class T>
class KnnClassifier {
    static_assert(std::is_base_of<Classifiable, T>::value, "T must be subclass of Classifiable!");
private:
    //The list of the classifiables to use in the algorithm
    std::vector<T> data;
    int k = 5;

    Distance<T> *distance = new EuclideanDistance<T>;

    //The comparator class
    class Comparator {
        //A classifiable that the class
        T compareTo;
        Distance<T> *distance_metric;
    public:
        //Compare using distances from the classifiable
        bool operator()(const T &t1, const T &t2) {
            return distance_metric->distance(compareTo, t1) < distance_metric->distance(compareTo, t2);
        }

        explicit Comparator(T t, Distance<T> *distance) : compareTo(t), distance_metric(distance) {
        }
    };

public:
    //Classify an unclassified
    std::string classify(T &unclassified) {
        if (data.empty()) {
            perror("Data is empty!");
        }

        //Sort the vector and get the first k elements
        std::stable_sort(data.begin(), data.end(), Comparator(unclassified, this->distance));
        //Count the appearances of each type
        std::map<std::string, int> predictions;
        for (int i = 0; i < k; i++) {
            if (predictions.count(data[i].getType()) == 0) {
                predictions[data[i].getType()] = 0;
            }
            predictions[data[i].getType()]++;

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
        int maxOccurrences = std::count_if(std::begin(predictions), std::end(predictions),
                                           [max](std::pair<std::string, int> const &p) { return p.second == max; });
        if (maxOccurrences > 1) {
            return data[0].getType();
        }

        return maxType;
    }

    void setData(const std::vector<T> &d) {
        this->data.clear();
        for (auto object: d) {
            this->data.push_back(object);
        }
    }

    void setDistance(Distance<T> *newDistance) {
        delete distance;
        this->distance = newDistance;
    }

    Distance<T> *getDistance() {
        return this->distance;
    }

    void setK(int newK) {
        this->k = newK;
    }

    std::string toString() const {
        return "The current KNN parameters are: K = " + std::to_string(k) + ", distance metric = " +
               distance->toString();
    }

    ~KnnClassifier() {
        delete distance;
    }

    KnnClassifier() = default;

    KnnClassifier(KnnClassifier &&o) noexcept = default;

    KnnClassifier(const KnnClassifier &o) = default;

    KnnClassifier &operator=(const KnnClassifier &) = default;
};


#endif //AP1_KNNCLASSIFIER_H
