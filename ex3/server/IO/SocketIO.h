#include "DefaultIO.h"
#include "../TCPServer.h"
#include "string"

#ifndef TESTING_SOCKETIO_H
#define TESTING_SOCKETIO_H


class SocketIO : public DefaultIO {
private:
    int socket;
public:
    explicit SocketIO(int socket);

    void write(std::string) override;

    std::string read() override;

    ~SocketIO();

};


#endif //TESTING_SOCKETIO_H
