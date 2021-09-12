#include <string>
#include <unistd.h>
#include <cstring>
#include "TCPClient.h"
#include "../utils.h"

void TCPClient::send(const std::string &string) const {
    utils::send(sock, string);
}


std::string TCPClient::recv() const {
    return utils::recv(sock);
}

void TCPClient::close() const {
    ::close(this->sock);
}

TCPClient::TCPClient(in_addr_t ip, in_port_t port) : sock(socket(AF_INET, SOCK_STREAM, 0)), sin() {
    //Initialize the socket and check it
    if (sock < 0) {
        perror("error creating socket");
    }
    //Initialize the data structure
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ip;
    sin.sin_port = port;

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
}

