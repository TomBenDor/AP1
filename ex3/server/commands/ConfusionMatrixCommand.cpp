#include "ConfusionMatrixCommand.h"
#include "Command.h"
#include "map"
#include "../ConfusionMatrix.h"

ConfusionMatrixCommand::ConfusionMatrixCommand(DefaultIO *io, std::vector<Iris> real, std::vector<Iris> predictions) :
        Command("display algorithm confusion matrix", io), real(std::move(real)), predictions(std::move(predictions)) {}

void ConfusionMatrixCommand::execute() {
    std::map<std::string, std::map<std::string, double>> typeMap;
    for (int i = 0; i < this->real.size(); i++) {
        if (!typeMap[real[i].getType()].count(predictions[i].getType())) {
            typeMap[real[i].getType()][predictions[i].getType()] = 0;
        }
        typeMap[real[i].getType()][predictions[i].getType()]++;
    }

    std::vector<std::string> types;
    for (const auto &pair: typeMap) {
        types.push_back(pair.first);
        double sum = 0;
        for (const auto &keys: pair.second) {
            sum += keys.second;
        }
        for (const auto &keys: pair.second) {
            typeMap[pair.first][keys.first] = 100 * keys.second / sum;
        }
    }

    for (const auto &pair: typeMap) {
        for (const std::string &type: types) {
            if (!typeMap[pair.first].count(type)) {
                typeMap[pair.first][type] = 0;
            }
        }
    }

    std::vector<std::vector<double>> matrix;
    for (const auto &predictionPercentage: typeMap) {
        std::vector<double> currPredictions;
        for (const auto &prediction: predictionPercentage.second) {
            currPredictions.push_back(prediction.second);
        }
        matrix.push_back(currPredictions);
    }

    ConfusionMatrix m(matrix, types);
    this->getDefaultIO()->write(m.toString());
}