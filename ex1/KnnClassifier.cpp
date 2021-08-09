#include "KnnClassifier.h"
#include "algorithm"
#include "Comparator.h"
#include "map"

std::string KnnClassifier::classify(Iris &unclassified) {
    std::sort(data.begin(), data.end(), Comparator(std::move(unclassified)));
    auto start = data.begin();
    auto end = data.begin() + k;
    std::vector<Iris> knn;
    for (auto i = start; i != end; i++) {
        knn.push_back(*i);
    }

    std::map<std::string, int> predictions;
    for (const Iris &iris:knn) {
        if (predictions.count(iris.getType()) == 0) {
            predictions[iris.getType()] = 0;
        }
        predictions[iris.getType()]++;

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

KnnClassifier::KnnClassifier(const std::vector<Iris> &data, int parameter) : k(parameter) {
    for (const Iris &iris: data) {
        this->data.push_back(iris);
    }
}
