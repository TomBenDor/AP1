#include "Command.h"
#include "KnnClassifier.h"
#include "../utils.h"
#include "stdexcept"
#include "ChebyshevDistance.h"
#include "EuclideanDistance.h"
#include "ManhattanDistance.h"
#include "algorithm"

#ifndef CLIENT_CHANGEALGOSETTINGS_H
#define CLIENT_CHANGEALGOSETTINGS_H

template<class T>
class ChangeAlgoSettings : public Command {
private:
    KnnClassifier<T> *algo;
public:
    void execute() override {
        this->getDefaultIO()->write(this->algo->toString());
        std::string input = this->getDefaultIO()->read();
        if (input.empty()) {
            this->getDefaultIO()->write(this->algo->toString());
            return;
        }
        std::vector<std::string> parameters = utils::split(input, ' ');
        if (parameters.size() != 2) {
            this->getDefaultIO()->write("Expected 2 parameters");
            return;
        }
        int k;
        try {
            k = std::stoi(parameters[0]);
        }
        catch (const std::invalid_argument &exception) {
            this->getDefaultIO()->write("K should be an int");
            return;
        }

        if (k > 10 || k < 1) {
            this->getDefaultIO()->write("K should be between 1 and 10");
            return;
        }
        Distance<T> *newDistance;
        std::string inputDistance = parameters[1];
        std::transform(inputDistance.begin(), inputDistance.end(), inputDistance.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        this->getDefaultIO()->write(inputDistance);
        if (inputDistance == "che") {
            newDistance = new ChebyshevDistance<T>;
        } else if (inputDistance == "man") {
            newDistance = new ManhattanDistance<T>;
        } else if (inputDistance == "euc") {
            newDistance = new EuclideanDistance<T>;
        } else {
            this->getDefaultIO()->write("Invalid distance metric");
            return;
        }
        this->algo->setK(k);
        this->algo->setDistance(newDistance);
        this->getDefaultIO()->write(this->algo->toString());
    }

    explicit ChangeAlgoSettings(DefaultIO *io, KnnClassifier<T> *classifier) : Command("algorithm settings", io),
                                                                               algo(classifier) {}
};


#endif //CLIENT_CHANGEALGOSETTINGS_H
