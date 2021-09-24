#include "Command.h"
#include "../KnnClassifier.h"
#include "../../utils.h"
#include "stdexcept"
#include "../metrics/ChebyshevDistance.h"
#include "../metrics/EuclideanDistance.h"
#include "../metrics/ManhattanDistance.h"
#include "algorithm"

#ifndef CLIENT_CHANGEALGOSETTINGS_H
#define CLIENT_CHANGEALGOSETTINGS_H

template<class T>
class ChangeAlgoSettingsCommand : public Command<T> {
public:
    void execute() override {
        this->getIO()->write(this->getData()->getClassifier()->toString());
        std::string input = this->getIO()->read();
        if (input.empty()) {
            this->getIO()->write(this->getData()->getClassifier()->toString());
            return;
        }
        std::vector<std::string> parameters = utils::split(input, ' ');
        if (parameters.size() != 2) {
            this->getIO()->write("Expected 2 parameters");
            return;
        }
        int k;
        try {
            k = std::stoi(parameters[0]);
        }
        catch (const std::invalid_argument &exception) {
            this->getIO()->write("K should be an int");
            return;
        }

        if (k > 10 || k < 1) {
            this->getIO()->write("K should be between 1 and 10");
            return;
        }
        Distance<T> *newDistance;
        std::string inputDistance = parameters[1];
        std::transform(inputDistance.begin(), inputDistance.end(), inputDistance.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        if (inputDistance == "che") {
            newDistance = new ChebyshevDistance<T>;
        } else if (inputDistance == "man") {
            newDistance = new ManhattanDistance<T>;
        } else if (inputDistance == "euc") {
            newDistance = new EuclideanDistance<T>;
        } else {
            this->getIO()->write("Invalid distance metric");
            return;
        }
        this->getData()->getClassifier()->setK(k);
        this->getData()->getClassifier()->setDistance(newDistance);
        this->getIO()->write(this->getData()->getClassifier()->toString());
    }

    explicit ChangeAlgoSettingsCommand(DefaultIO *io, ClientData<T> *data) : Command<T>("algorithm settings", io,
                                                                                        data) {}
};


#endif //CLIENT_CHANGEALGOSETTINGS_H
