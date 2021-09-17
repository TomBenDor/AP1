#include "DefaultIO.h"

#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H


class Command {
private:
    std::string description;
    DefaultIO *io;
public:
    virtual std::string getDescription();

    virtual DefaultIO *getDefaultIO();

    virtual void execute() = 0;

    Command(std::string description, DefaultIO *io);
};


#endif //CLIENT_COMMAND_H
