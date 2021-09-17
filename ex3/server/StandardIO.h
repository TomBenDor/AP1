#include "DefaultIO.h"

#ifndef CLIENT_STANDARDIO_H
#define CLIENT_STANDARDIO_H


class StandardIO : public DefaultIO {
public:
    void write(std::string string) override;

    std::string read() override;
};


#endif //CLIENT_STANDARDIO_H
