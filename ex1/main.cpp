#include <vector>
#include <iostream>
#include "Iris.h"
#include "utils.h"
#include "KnnClassifier.h"

int main(int argc, char *argv[]) {
    std::vector<Iris> classified = toIrisVector(readCSV(argv[1]));
    std::vector<Iris> unclassified = toIrisVector(readCSV(argv[2]));

    KnnClassifier<Iris> classifier(classified, 5);

    std::vector<std::string> result;
    result.reserve(unclassified.size());
    for (auto iris: unclassified) {
        result.push_back(classifier.classify(iris));
    }

    writeCSV(argv[3], result);
}
