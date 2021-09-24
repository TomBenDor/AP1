#include <utility>

#include "../IO/DefaultIO.h"
#include "../ClientData.h"

#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H

template<class T>
class Command {
private:
    std::string description;
    DefaultIO *io;
    ClientData<T> *data;
public:
    std::string getDescription() {
        return std::string(description);
    }

    DefaultIO *getIO() {
        return io;
    }

    ClientData<T> *getData() const {
        return data;
    }

    virtual void execute() = 0;

    Command(std::string description, DefaultIO *io, ClientData<T> *data) : description(std::move(description)), io(io),
                                                                           data(data) {}
};


#endif //CLIENT_COMMAND_H
