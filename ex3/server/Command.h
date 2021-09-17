#include "DefaultIO.h"

#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H


class Command {
private:
    std::string description;
    DefaultIO *io;
public:
    virtual std::string getDescription() = 0;

    virtual void execute() = 0;

    Command(const std::string &description, DefaultIO *io);
};


#endif //CLIENT_COMMAND_H
