#include "Command.h"
#include "vector"
#include "../Iris.h"
#include "../IO/DefaultIO.h"
#include "../ClientData.h"

#ifndef CLIENT_UPLOADUNCLASSIFIED_H
#define CLIENT_UPLOADUNCLASSIFIED_H

template<class T>
class UploadUnclassifiedCommand : public Command<T> {
public:
    void execute() override {
        this->getIO()->write("Please upload your local train csv file");
        std::string input = this->getIO()->read();
        try {
            this->getData()->setTrain(stringToIrisVector(input, true));
        }
        catch (const std::invalid_argument &e) {
            this->getIO()->write("Upload a valid file");
            return;
        }
        this->getIO()->write("Upload Complete.");
        this->getIO()->write("Please upload your local test csv file");
        input = this->getIO()->read();
        try {
            this->getData()->setTest(stringToIrisVector(input, true));
        }
        catch (const std::invalid_argument &e) {
            this->getIO()->write("Upload a valid file");
            return;
        }
        this->getIO()->write("Upload Complete");
    }

    UploadUnclassifiedCommand(DefaultIO *io, ClientData<Iris> *data) :
            Command<T>("upload an unclassified csv data file", io, data) {}
};


#endif //CLIENT_UPLOADUNCLASSIFIED_H
