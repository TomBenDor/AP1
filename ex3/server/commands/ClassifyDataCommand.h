#include "Command.h"
#include "thread"

#ifndef TESTING_CLASSIFYDATACOMMAND_H
#define TESTING_CLASSIFYDATACOMMAND_H

template<class T>
class ClassifyDataCommand : public Command<T> {
public:
    void execute() override {
        this->getIO()->write("Started classifying");
        std::thread classifying([this] { this->getData()->classify(); });
        classifying.detach();
    }

    ClassifyDataCommand(DefaultIO *io, ClientData<T> *data) : Command<T>("classify data", io, data) {}
};

#endif //TESTING_CLASSIFYDATACOMMAND_H
