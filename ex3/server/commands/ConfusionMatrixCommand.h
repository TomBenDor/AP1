#include "Command.h"
#include "vector"
#include "string"
#include "../Iris.h"
#include "../KnnClassifier.h"
#include "../ConfusionMatrix.h"

#ifndef TESTING_CONFUSIONMATRIXCOMMAND_H
#define TESTING_CONFUSIONMATRIXCOMMAND_H

template<class T>
class ConfusionMatrixCommand : public Command<T> {
public:
    ConfusionMatrixCommand(DefaultIO *io, ClientData<T> *data) : Command<T>("display algorithm confusion matrix", io,
                                                                            data) {}

    void execute() override {
        std::vector<T> test = this->getData()->getTest();
        std::vector<std::string> predictions = this->getData()->getClassified();
        if (predictions.empty()) {
            this->getIO()->write("Classify first");
            return;
        }
        //Create a map containing all predictions and types
        std::map<std::string, std::map<std::string, double>> typeMap;
        for (int i = 0; i < test.size(); i++) {
            if (!typeMap[test[i].getType()].count(predictions[i])) {
                typeMap[test[i].getType()][predictions[i]] = 0;
            }
            typeMap[test[i].getType()][predictions[i]]++;
        }

        std::vector<std::string> types;
        for (const auto &pair: typeMap) {
            //Save all test types
            types.push_back(pair.first);
            //sum all predictions
            double sum = 0;
            for (const auto &keys: pair.second) {
                sum += keys.second;
            }
            //Convert the numbers to percentages
            for (const auto &keys: pair.second) {
                typeMap[pair.first][keys.first] = 100 * keys.second / sum;
            }
        }
        //Add missing types
        for (const auto &pair: typeMap) {
            for (const std::string &type: types) {
                if (!typeMap[pair.first].count(type)) {
                    typeMap[pair.first][type] = 0;
                }
            }
        }
        //Convert the map to a matrix of strings
        std::vector<std::vector<std::string>> matrix;
        for (const auto &predictionPercentage: typeMap) {
            std::vector<std::string> currPredictions;
            for (const auto &prediction: predictionPercentage.second) {
                currPredictions.push_back(std::to_string(prediction.second));
            }
            matrix.push_back(currPredictions);
        }

        ConfusionMatrix m(matrix, types);
        this->getIO()->write(m.toString());
        this->getIO()->write(this->getData()->getClassifier()->toString());
    }
};


#endif //TESTING_CONFUSIONMATRIXCOMMAND_H
