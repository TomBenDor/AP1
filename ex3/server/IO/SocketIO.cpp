#include "SocketIO.h"
#include "string"
#include "../../utils.h"
#include <unistd.h>

SocketIO::SocketIO(int socket) : socket(socket) {}

std::string SocketIO::read() {
    return utils::recv(this->socket);
}

void SocketIO::write(std::string msg) {
    utils::send(this->socket, msg);
}

SocketIO::~SocketIO() {
    close(this->socket);
}