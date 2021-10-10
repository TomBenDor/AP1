#ifndef TESTING_DOWNLOADRESULTSCOMMAND_H
#define TESTING_DOWNLOADRESULTSCOMMAND_H

#include "sstream"

template<class T>
class DownloadResultsCommand : public Command<T> {
public:
    void execute() override {
        if (this->getData()->getClassified().empty()) {
            this->getIO()->write("Classify first to get results");
            return;
        }
        this->getIO()->write("Enter path for the output file");
        std::string path = this->getIO()->read();
        std::stringstream msg;
        msg << "SAVE <";
        for (int i = 0; i < this->getData()->getClassified().size(); i++) {
            msg << std::to_string(i + 1) + '\t' + this->getData()->getClassified()[i] << "\n";
        }
        msg << "Done." << "> " << "TO <" << path << ">";
        this->getIO()->write(msg.str());
        this->getIO()->read(); // Waiting for client to press enter.
    }

    DownloadResultsCommand(DefaultIO *io, ClientData<T> *data) : Command<T>("download data", io, data) {}
};


#endif //TESTING_DOWNLOADRESULTSCOMMAND_H
