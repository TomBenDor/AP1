#include "Command.h"

#ifndef TESTING_DISPLAYRESULTSCOMMAND_H
#define TESTING_DISPLAYRESULTSCOMMAND_H

template<class T>
class DisplayResultsCommand : public Command<T> {
public:
    void execute() override {
        if (this->getData()->getClassified().empty()) {
            this->getIO()->write("Classify first to get results");
            return;
        }
        for (int i = 0; i < this->getData()->getClassified().size(); i++) {
            this->getIO()->write(std::to_string(i + 1) + '\t' + this->getData()->getClassified()[i]);
        }
        this->getIO()->write("Done.");
        this->getIO()->read(); // Waiting for client to press enter.
    }

    DisplayResultsCommand(DefaultIO *io, ClientData<T> *data) : Command<T>("display data", io, data) {}
};


#endif //TESTING_DISPLAYRESULTSCOMMAND_H
