#include "Command.h"

#ifndef TESTING_CLASSIFYDATACOMMAND_H
#define TESTING_CLASSIFYDATACOMMAND_H

template<class T>
class ClassifyDataCommand : public Command<T> {
public:
    void execute() override {
        this->getData()->classify();
        this->getIO()->write("classifying data complete");
    }

    ClassifyDataCommand(DefaultIO *io, ClientData<T> *data) : Command<T>("classify data", io, data) {}
};

#endif //TESTING_CLASSIFYDATACOMMAND_H
