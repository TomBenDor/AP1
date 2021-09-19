#include "Command.h"
#include "KnnClassifier.h"
#include "../utils.h"
#include "stdexcept"
#include "ChebyshevDistance.h"
#include "EuclideanDistance.h"
#include "ManhattanDistance.h"

#ifndef CLIENT_CHANGEALGOSETTINGS_H
#define CLIENT_CHANGEALGOSETTINGS_H

template<class T>
class changeAlgoSettings : public Command {
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
        ChebyshevDistance<T> chebyshevDistance;
        ManhattanDistance<T> manhattanDistance;
        EuclideanDistance<T> euclideanDistance;
        std::string inputDistance = parameters[1];
        if (inputDistance == "CHE" || inputDistance == "che") {
            newDistance = &chebyshevDistance;
        } else if (inputDistance == "MAN" || inputDistance == "man") {
            newDistance = &manhattanDistance;
        } else if (inputDistance == "EUC" || inputDistance == "euc") {
            newDistance = &euclideanDistance;
        } else {
            this->getDefaultIO()->write("Invalid distance metric");
            return;
        }
        this->algo->setK(k);
        this->algo->setDistance(newDistance);
        this->getDefaultIO()->write(this->algo->toString());
    }

    explicit changeAlgoSettings(DefaultIO *io, KnnClassifier<T> *classifier) : Command("algorithm settings", io),
                                                                               algo(classifier) {}
};


#endif //CLIENT_CHANGEALGOSETTINGS_H
