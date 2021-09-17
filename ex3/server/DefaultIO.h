#include "string"

#ifndef CLIENT_DEFAULTIO_H
#define CLIENT_DEFAULTIO_H


class DefaultIO {
    virtual std::string read() = 0;

    virtual void write(std::string) = 0;
};


#endif //CLIENT_DEFAULTIO_H
