#include "Command.h"
#include "vector"
#include "../Iris.h"
#include "../IO/SocketIO.h"
#include "../ClientData.h"

#ifndef CLIENT_UPLOADUNCLASSIFIED_H
#define CLIENT_UPLOADUNCLASSIFIED_H

template<class T>
class UploadUnclassifiedCommand : public Command<T> {
public:
    void execute() override {
        this->getIO()->write("Please upload your local train csv file");
        std::string input = this->getIO()->read();
        this->getData()->setTrain(stringToIrisVector(input, true));
        this->getIO()->write("Upload Complete.");
        this->getIO()->write("Please upload your local test csv file");

        input = this->getIO()->read();
        this->getData()->setTest(stringToIrisVector(input, true));
        this->getIO()->write("Upload Complete");
    }

    UploadUnclassifiedCommand(SocketIO *io, ClientData<Iris> *data) : Command<T>("upload an unclassified csv data file",
                                                                                 io, data) {}
};


#endif //CLIENT_UPLOADUNCLASSIFIED_H
